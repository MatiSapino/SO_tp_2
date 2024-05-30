#include <defs.h>
#include <lib.h>
#include <libasm.h>
#include <linkedList.h>
#include <process.h>
#include <memory_manager.h>
#include <scheduler.h>
#include <stdlib.h>
#define MAX_PRIORITY 4
#define MIN_PRIORITY 0
#define BLOCKED_INDEX PRIORITY_LEVELS
#define IDLE_PID 0

extern void force_tick();


scheduler_ptr create_scheduler() {
	scheduler_ptr scheduler = (scheduler_ptr) SCHEDULER_ADDRESS;
	for (int i = 0; i < MAX_PROCESSES_AMOUNT; i++)
		scheduler->processes[i] = NULL;
	for (int i = 0; i < PRIORITY_LEVELS + 1; i++)
		scheduler->levels[i] = new_linked_list((int (*)(void *, void *))search_by_pid);
	scheduler->next_available_pid = 0;
	scheduler->kill_foreground_p = 0;
	return scheduler;
}

scheduler_ptr get_scheduler() {
	return (scheduler_ptr) SCHEDULER_ADDRESS;
}

static uint16_t get_next_pid(scheduler_ptr scheduler) {
	process_ptr process = NULL;
	for (int lvl = PRIORITY_LEVELS - 1; lvl >= 0 && process == NULL; lvl--)
		if (!is_empty(scheduler->levels[lvl]))
			process = (process_ptr) (get_first(scheduler->levels[lvl]))->data;

	if (process == NULL)
		return IDLE_PID;
	return process->pid;
}

int32_t set_priority(uint16_t pid, uint8_t new_priority) {
	scheduler_ptr scheduler = get_scheduler();
	node_ptr node = scheduler->processes[pid];
	if (node == NULL || pid == IDLE_PID)
		return -1;
	process_ptr process = (process_ptr) node->data;
	if (new_priority >= PRIORITY_LEVELS)
		return -1;
	if (process->status == READY || process->status == RUNNING) {
		remove_node(scheduler->levels[process->priority], node);
		scheduler->processes[process->pid] = append_node(scheduler->levels[new_priority], node);
	}
	process->priority = new_priority;
	return new_priority;
}

int8_t set_status(uint16_t pid, uint8_t newStatus) {
	scheduler_ptr scheduler = get_scheduler();
	node_ptr node = scheduler->processes[pid];
	if (node == NULL || pid == IDLE_PID)
		return -1;
	process_ptr process = (process_ptr) node->data;
	pstatus_t oldStatus = process->status;
	if (newStatus == RUNNING || newStatus == ZOMBIE || oldStatus == ZOMBIE)
		return -1;
	if (newStatus == process->status)
		return newStatus;

	process->status = newStatus;
	if (newStatus == BLOCKED) {
		remove_node(scheduler->levels[process->priority], node);
		append_node(scheduler->levels[BLOCKED_INDEX], node);
		// setPriority(pid, process->priority == MAX_PRIORITY ? MAX_PRIORITY : process->priority + 1);
	}
	else if (oldStatus == BLOCKED) {
		remove_node(scheduler->levels[BLOCKED_INDEX], node);
		// Se asume que ya tiene un nivel predefinido
		// append_node(scheduler->levels[process->priority], node);
		process->priority = MAX_PRIORITY;
		prepend_node(scheduler->levels[process->priority], node);
		scheduler->quantums_left = 0;
	}
	return newStatus;
}

pstatus_t get_pstatus(uint16_t pid) {
	scheduler_ptr scheduler = get_scheduler();
	node_ptr my_process = scheduler->processes[pid];
	if (my_process == NULL)
		return DEAD;
	return ((process_ptr) my_process->data)->status;
}

void *schedule(void *prevStackPointer) {
	static int firstTime = 1;
	scheduler_ptr scheduler = get_scheduler();

	scheduler->quantums_left--;
	if (!scheduler->process_amount || scheduler->quantums_left > 0)
		return prevStackPointer;

	process_ptr currentProcess;
	node_ptr currentProcessNode = scheduler->processes[scheduler->pid];

	if (currentProcessNode != NULL) {
		currentProcess = (process_ptr) currentProcessNode->data;
		if (!firstTime)
			currentProcess->stack_position = prevStackPointer;
		else
			firstTime = 0;
		if (currentProcess->status == RUNNING)
			currentProcess->status = READY;

		uint8_t newPriority = currentProcess->priority > 0 ? currentProcess->priority - 1 : currentProcess->priority;
		set_priority(currentProcess->pid, newPriority);
	}

	scheduler->pid = get_next_pid(scheduler);
	currentProcess = scheduler->processes[scheduler->pid]->data;

	if (scheduler->kill_foreground_p && currentProcess->fread == STDIN) {
		scheduler->kill_foreground_p = 0;
		if (kill_current_process(-1) != -1)
			force_tick();
	}
	scheduler->quantums_left = (MAX_PRIORITY - currentProcess->priority);
	currentProcess->status = RUNNING;
	return currentProcess->stack_position;
}

int16_t createProcess(function_t code, int argc, char **argv, char *name, uint8_t priority, int16_t fds[], uint8_t is_init) {
	scheduler_ptr scheduler = get_scheduler();
	if (scheduler->process_amount >= MAX_PROCESSES_AMOUNT) // TODO: Agregar panic?
		return -1;
	process_ptr process = (process_ptr) mem_alloc(sizeof(process_t));
	set_p_params(process, scheduler->next_available_pid, scheduler->pid, code, argc, argv, name, priority, is_init, fds);

	node_ptr processNode;
	if (process->pid != IDLE_PID)
		processNode = add(scheduler->levels[process->priority], (void *) process);
	else {
		processNode = mem_alloc(sizeof(node_t));
		processNode->data = (void *) process;
	}
	scheduler->processes[process->pid] = processNode;

	while (scheduler->processes[scheduler->next_available_pid] != NULL)
		scheduler->next_available_pid = (scheduler->next_available_pid + 1) % MAX_PROCESSES_AMOUNT;
	scheduler->process_amount++;
	return process->pid;
}

static void destroyZombie(scheduler_ptr scheduler, process_ptr zombie) {
	node_ptr zombieNode = scheduler->processes[zombie->pid];
	scheduler->process_amount--;
	scheduler->processes[zombie->pid] = NULL;
	free_process(zombie);
	free(zombieNode);
}

int32_t kill_current_process(int32_t ret_value) {
	scheduler_ptr scheduler = get_scheduler();
	return kill_process(scheduler->pid, ret_value);
}

int32_t kill_process(uint16_t pid, int32_t ret_value) {
	scheduler_ptr scheduler = get_scheduler();
	node_ptr pnode_to_kill = scheduler->processes[pid];
	if (pnode_to_kill == NULL)
		return -1;
	process_ptr process_to_kill = (process_ptr) pnode_to_kill->data;
	if (process_to_kill->status == ZOMBIE || process_to_kill->is_init)
		return -1;

	close_fds(process_to_kill);

	uint8_t priorityIndex = process_to_kill->status != BLOCKED ? process_to_kill->priority : BLOCKED_INDEX;
	remove_node(scheduler->levels[priorityIndex], pnode_to_kill);
	process_to_kill->ret_value = ret_value;

	process_to_kill->status = ZOMBIE;

	to_begin(process_to_kill->zombies);
	while (has_next(process_to_kill->zombies)) {
		destroyZombie(scheduler, (process_ptr) next(process_to_kill->zombies));
	}

	node_ptr parentNode = scheduler->processes[process_to_kill->parent_pid];
	if (parentNode != NULL && ((process_ptr) parentNode->data)->status != ZOMBIE) {
		process_ptr parent = (process_ptr) parentNode->data;
		append_node(parent->zombies, pnode_to_kill);
		if (is_waiting(parent, process_to_kill->pid))
			set_pstatus(process_to_kill->parent_pid, READY);
	}
	else {
		destroyZombie(scheduler, process_to_kill);
	}
	if (pid == scheduler->pid)
		yield();
	return 0;
}

uint16_t getpid() {
	scheduler_ptr scheduler = get_scheduler();
	return scheduler->pid;
}

psnapshot_ptr * get_psnapshot() {
	scheduler_ptr scheduler = get_scheduler();
	psnapshot_ptr * psnapshot_array = mem_alloc(scheduler->process_amount * sizeof(psnapshot_t));
	int process_index = 0;

	load_snapshot(psnapshot_array[process_index++], (process_ptr) scheduler->processes[IDLE_PID]->data);
	for (int lvl = PRIORITY_LEVELS; lvl >= 0; lvl--) { // Se cuentan tambien los bloqueados
		to_begin(scheduler->levels[lvl]);
		while (has_next(scheduler->levels[lvl])) {
			process_ptr next_p_in_schedule = (process_ptr) next(scheduler->levels[lvl]);
			load_snapshot(psnapshot_array[process_index], next_p_in_schedule);
			process_index++;
			if (next_p_in_schedule->status != ZOMBIE) {
				load_zombies_snapshot(process_index, *psnapshot_array, next_p_in_schedule);
				process_index += get_length(next_p_in_schedule->zombies);
			}
		} 
	}
	return psnapshot_array;
}

int32_t get_zombie_ret_value(uint16_t pid) {
	scheduler_ptr scheduler = get_scheduler();
	node_ptr zombieNode = scheduler->processes[pid];
	if (zombieNode == NULL)
		return -1;
	process_ptr zombieProcess = (process_ptr) zombieNode->data;
	if (zombieProcess->parent_pid != scheduler->pid)
		return -1;

	process_ptr parent = (process_ptr) scheduler->processes[scheduler->pid]->data;
	if (zombieProcess->status != ZOMBIE) {
		set_pstatus(parent->pid, BLOCKED);
		yield();
	}
	remove_node(parent->zombies, zombieNode);
	destroyZombie(scheduler, zombieProcess);
	return zombieProcess->ret_value;
}

int32_t p_still_alive(uint16_t pid) {
	scheduler_ptr scheduler = get_scheduler();
	node_ptr processNode = scheduler->processes[pid];
	return processNode != NULL && ((process_ptr) processNode->data)->status != ZOMBIE;
}

void yield() {
	scheduler_ptr scheduler = get_scheduler();
	scheduler->quantums_left = 0;
	force_tick();
}

int8_t change_fd(uint16_t pid, uint8_t std, int16_t new_fd) {
	scheduler_ptr scheduler = get_scheduler();
	node_ptr processNode = scheduler->processes[pid];
	if (pid == IDLE_PID || processNode == NULL)
		return -1;
	process_ptr process = (process_ptr) processNode->data;
    if (std == STDIN) process->fread = new_fd;
    if (std == STDOUT) process->fwrite = new_fd;
    if (std == STDERR) process->ferror = new_fd;
    

	return 0;
}

int16_t get_current_p_fd(uint8_t std) {
	scheduler_ptr scheduler = get_scheduler();
	process_ptr process = scheduler->processes[scheduler->pid]->data;
    if (std == STDIN) return process->fread;
    if (std == STDOUT) return process->fwrite;
    if (std == STDERR) return process->ferror;

}

void kill_foreground_p() {
	scheduler_ptr scheduler = get_scheduler();
	scheduler->kill_foreground_p = 1;
}