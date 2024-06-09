#include <lib.h>
#include <lib/defs.h>
#include <linked_list.h>
#include "../include/pipe/pipe.h"
#include <pmm.h>
#include <scheduler.h> 

static list_ptr pipe_list;

static int comparison_function(void *pipe, void *name) {
    pipe_ptr pipe_test = (pipe_ptr)pipe;
    char *name_test = (char *)name;

    return !strcmp(pipe_test->name, name_test);
}

static int process_pipe_comparison_function(void * pid, void * other_pid){
    return (*(int *)pid) == (*(int *)other_pid);
}

static void wakeup_helper(void * channel, list_ptr blocked_list) {
    int pid = wakeup(channel);
    remove(blocked_list, (void *)&pid);
}

static void sleep_helper(void * channel,list_ptr blocked_list){
    process_ptr process = get_current_process();
    add(blocked_list, &(process->pid));
    sleep(channel);
}

static void set_data_descriptors(pipe_ptr pipe, int pipe_dataD[2]) {

    data_descriptor_ptr readEnd = create_dataDescriptor(PIPE_T, READ_MODE);
    setPipe_dataDescriptor(readEnd, pipe);
    pipe->readopen++;

    data_descriptor_ptr writeEnd = create_dataDescriptor(PIPE_T, WRITE_MODE);
    setPipe_dataDescriptor(writeEnd, pipe);
    pipe->writeopen++;

    process_ptr process = get_current_process();
    pipe_dataD[0] = process->data_d_index;
    process->data_descriptors[process->data_d_index++] = readEnd;
    pipe_dataD[1] = process->data_d_index;
    process->data_descriptors[process->data_d_index++] = writeEnd;
}

int init_pipes() {
    pipe_list = new_linked_list(comparison_function);
    return 0;
}

int create_pipe(char *name, int pipe_dataD[2]) {

    if (pipe_list == NULL)
        init_pipes();

    if (find(pipe_list, name, NULL) != NULL) {
        return -1;
    }

    pipe_ptr newPipe = kmalloc(sizeof(pipe_t));
    if (newPipe == NULL)
        return -1;

    newPipe->name = name;
    newPipe->nread = 0;
    newPipe->nwrite = 0;
    newPipe->readopen = 0;
    newPipe->writeopen = 0;
    newPipe->blocked_pid = new_linked_list(process_pipe_comparison_function);

    add(pipe_list, newPipe);

    set_data_descriptors(newPipe, pipe_dataD);

    return 0;
}

int open_pipe(char *name, int pipe_dataD[2]) {

    if (pipe_list == NULL)
        return -1;

    pipe_ptr pipe = find(pipe_list, name, NULL);

    if (pipe == NULL) {
        return -1;
    }

    set_data_descriptors(pipe, pipe_dataD);

    return 0;
}

int pipewrite(pipe_ptr pipe, const char *buffer, int count) {

    if (pipe == NULL || buffer == NULL || count < 0)
        return -2;

    int i;
    for (i = 0; i < count; i++) {
        while (pipe->nwrite == pipe->nread + PIPE_SIZE) {
            wakeup_helper(&pipe->nread, pipe->blocked_pid);
            sleep_helper(&pipe->nwrite, pipe->blocked_pid);
        }
        pipe->data[pipe->nwrite++ % PIPE_SIZE] = buffer[i];
    }
    wakeup_helper(&pipe->nread, pipe->blocked_pid);

    return i;
}

int piperead(pipe_ptr pipe, char *buffer, int count) {

    if (pipe == NULL || buffer == NULL || count < 0)
        return -2;

    while (pipe->nread == pipe->nwrite) {
        if (pipe->writeopen == 0)
            return EOF;
        sleep_helper(&pipe->nread, pipe->blocked_pid);
    }

    int i;
    for (i = 0; i < count; i++) {
        if (pipe->nread == pipe->nwrite)
            break;
        buffer[i] = pipe->data[pipe->nread++ % PIPE_SIZE];
    }
    wakeup_helper(&pipe->nwrite, pipe->blocked_pid);

    if (pipe->nread == pipe->nwrite + 1)
        return EOF;

    return i;
}

void close_pipe(pipe_ptr pipe, int writable) {

    if (pipe_list == NULL || pipe == NULL)
        return;

    if (writable) {
        if (pipe->writeopen != 0) {
            pipe->writeopen--;
            wakeup_helper(&pipe->nread, pipe->blocked_pid);
        }
    } else {
        if (pipe->readopen != 0) {
            pipe->readopen--;
            wakeup_helper(&pipe->nread, pipe->blocked_pid);
        }
    }

    if (pipe->readopen == 0 && pipe->writeopen == 0 && pipe->nread > 0 &&
        pipe->nwrite > 0) {
        remove(pipe_list, pipe->name);
        free_list(pipe->blocked_pid);
        kfree(pipe);
    }

    to_begin(pipe_list);

    if (!hasNext(pipe_list)) {
        kfree(pipe_list);
        pipe_list = NULL;
    }

    return;
}

static int copy_pids(list_ptr blocked_pid, int blocked_pid_cpy[]) {

    to_begin(blocked_pid);

    int count = 0;

    while (hasNext(blocked_pid)) {
        int pid = *(int *)next(blocked_pid);
        blocked_pid_cpy[count++] = pid;
    }

    return count;
}

static void copy_info(pipe_ptr pipe, pipe_info_ptr info) {

    info->name = pipe->name;
    info->nread = pipe->nread;
    info->nwrite = pipe->nwrite;
    info->readopen = pipe->readopen;
    info->writeopen = pipe->writeopen;

    info->blocked_count = copy_pids(pipe->blocked_pid, info->blocked_pid);
}

int info_pipe(char *name, pipe_info_ptr info) {

    pipe_ptr pipe = find(pipe_list, name, NULL);
    if (pipe == NULL)
        return -1;

    copy_info(pipe, info);

    return 0;
}

int info_all_pipes(pipe_info_ptr info_arr[], unsigned int size) {

    int count = 0;

    if (pipe_list == NULL)
        return 0;

    to_begin(pipe_list);

    while (hasNext(pipe_list) && count < size) {
        copy_info((pipe_ptr)next(pipe_list), info_arr[count++]);
    }

    return count;
}

void add_writer(pipe_ptr pipe) {
    pipe->nwrite++;
}

void add_reader(pipe_ptr pipe) {
    pipe->nread++;
} 