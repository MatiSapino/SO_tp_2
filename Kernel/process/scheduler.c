#include <timer.h> 
#include <circular_linked_list.h>
#include <idtLoader.h>
#include <lib/linked_list.h>
#include <pmm.h>
#include "../include/process/process.h"
#include "../include/process/scheduler.h"
#include <stdbool.h>

#define PID_ERR        -1
#define MAX_TERM_COUNT 2

static circular_list_ptr process_list;
static circular_list_iterator_ptr rr_iterator;

static process_ptr current_process;
static process_ptr foreground_process;

static int priority_timer_tick = 0;

static void remove_process(int pid);

int search_by_status(void *process, void *status) {
    return ((process_ptr)process)->status == *((pstatus_ptr)status);
}

static int search_by_channel(void *process, void *channel) {
    return ((process_ptr)process)->status == WAITING &&
           ((process_ptr)process)->channel == channel;
}

void init_scheduler() {
    process_list = new_circular_linked_list(search_by_pid);
    rr_iterator = new_circular_list_iterator(process_list);
    cl_subscribe_iterator(process_list, rr_iterator);
}

int process_count() {
    return cl_size(process_list);
}

pid_t wait_process(pid_t pid, int *status_ptr) {

    // if no children, return
    if (size(current_process->children) == 0 || pid < -1)
        return PID_ERR;

    list_ptr children_list = current_process->children;
    process_ptr target_child = NULL;

    while (true) {
        if (pid >= 0) {
            target_child = find(children_list, &pid, NULL);

            if (target_child != NULL && target_child->status == TERMINATED) {
                if (status_ptr != NULL)
                    *status_ptr = target_child->exit_status;
                remove_process(target_child->pid);
                return target_child->pid;
            }
        } else {
            int terminated = TERMINATED;
            target_child = find(children_list, &terminated, search_by_status);

            if (target_child != NULL) {
                if (status_ptr != NULL)
                    *status_ptr = target_child->exit_status;
                remove_process(target_child->pid);
                return target_child->pid;
            }
        }

        sleep(current_process);
    }
}

void sleep(void * channel) {
    current_process->channel = channel;
    current_process->status = WAITING;
    _force_schedule();
}

int wakeup(void * channel) {
    process_ptr target = cl_find(process_list, channel, search_by_channel);
    if (target == NULL)
        return PID_ERR;

    target->status = READY;
    target->channel = NULL;

    return target->pid;
}

int add_process(function_t main, int argc, char *argv[]) {
    if (process_count() >= MAX_PROC_COUNT)
        return PID_ERR;

    process_ptr process = new_process(main, argc, argv);
    if (process == NULL)
        return PID_ERR;

    cl_add(process_list, process);

    if (current_process != NULL) {
        add(current_process->children, process);
        process->parent = current_process;
    }

    return process->pid;
}

static void remove_children(process_ptr process) {
    if (size(process->children) == 0)
        return;

    to_begin(process->children);
    while (hasNext(process->children)) {
        process_ptr child = next(process->children);
        remove_process(child->pid);
    }
}

static void remove_process(int pid) {
    process_ptr target = cl_remove(process_list, &pid);
    if (target == NULL)
        return;

    if (target == foreground_process)
        foreground_process = NULL;

    // remove process from parent's children list
    remove(target->parent->children, &pid);
    free_process(target);
}

void exit_process(int status) {
    close_dataDescriptor(current_process->data_descriptors[0]);
    close_dataDescriptor(current_process->data_descriptors[1]);

    current_process->data_descriptors[0] = NULL;
    current_process->data_descriptors[1] = NULL;

    remove_children(current_process);
    wakeup(current_process->parent);

    // leave process as terminated. Parent will clean it up on wait
    current_process->status = TERMINATED;
    current_process->exit_status = status;

    _force_schedule();
}

int kill_process(int pid) {
    process_ptr target = cl_find(process_list, &pid, search_by_pid);
    if (target == NULL)
        return PID_ERR;

    close_dataDescriptor(target->data_descriptors[0]);
    close_dataDescriptor(target->data_descriptors[1]);

    remove_children(target);
    wakeup(target->parent);

    // leave process as terminated. Parent will clean it up on wait
    target->status = TERMINATED;
    target->exit_status = -1;
    if (target == current_process)
        _force_schedule();

    return pid;
}

process_ptr get_current_process() {
    return current_process;
}

process_ptr get_process(pid_t pid) {
    return cl_find(process_list, &pid, search_by_pid);
}

void set_foreground_process(int pid) {
    process_ptr found = cl_find(process_list, &pid, search_by_pid);
    if (found == NULL)
        return;

    // set the new foreground process priority to the highest
    foreground_process->priority = LOWEST;
    foreground_process = found;
    foreground_process->priority = HIGHEST;
}

process_ptr get_foreground_process() {
    return foreground_process;
}

int get_process_table(process_table_t *table) {
    circular_list_iterator_ptr iterator = new_circular_list_iterator(process_list);

    int row = 0;
    cl_subscribe_iterator(process_list, iterator);
    cl_to_begin(process_list, iterator);
    while (cl_has_next(iterator) && row < PROCESS_TABLE_MAX_SIZE) {
        process_t *process = cl_next(iterator);

        table->entries[row].pid = process->pid;
        table->entries[row].priority = process->priority;
        table->entries[row].status = process->status;
        table->entries[row].rbp = process->context->rbp;
        table->entries[row].stack = process->context;
        table->entries[row].children_count = size(process->children);

        if (process->parent != NULL)
            strcpy(table->entries[row].parent_name, process->parent->argv[0]);
        else
            strcpy(table->entries[row].parent_name, "-");

        strcpy(table->entries[row].name, process->argv[0]);

        row++;
    }

    table->count = row;
    cl_unsubscribe_iterator(process_list, iterator);
    cl_free_iterator(iterator);

    return row;
}

context_ptr schedule(context_t *rsp) {
    if (process_count() == 0)
        return rsp;

    if (current_process != NULL && current_process->status == READY &&
        priority_timer_tick < current_process->priority) {
        priority_timer_tick++;
        return rsp;
    }

    if (current_process != NULL)
        current_process->context = rsp;

    do {
        current_process = cl_next(rr_iterator);
    } while (current_process->status != READY);

    // set timer ticks to 0
    priority_timer_tick = 0;

    return current_process->context;
}
