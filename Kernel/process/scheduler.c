#include <defs.h>
#include <lib.h>
#include <linkedList.h>
#include <process.h>
#include <memory_manager.h>
#include <scheduler.h>
#include <stdlib.h>
#define MAX_PRIORITY 4
#define MIN_PRIORITY 0
#define BLOCKED_INDEX PRIORITY_LEVELS
#define MAX_PROCESSES (1 << 12)
#define IDLE_PID 0
#define QUANTUM_COEF 2


scheduler_ptr create_scheduler() {
	scheduler_ptr scheduler = (scheduler_ptr) SCHEDULER_ADDRESS;
	for (int i = 0; i < MAX_PROCESSES; i++)
		scheduler->processes[i] = NULL;
	for (int i = 0; i < PRIORITY_LEVELS + 1; i++)
		scheduler->levels[i] = new_linked_list((int (*)(void *, void *))search_by_pid);
	scheduler->nextUnusedPid = 0;
	scheduler->killFgProcess = 0;
	return scheduler;
}

scheduler_ptr get_scheduler() {
	return (scheduler_ptr) SCHEDULER_ADDRESS;
}

static uint16_t get_next_pid(scheduler_ptr scheduler) {
	process_ptr process = NULL;
	for (int lvl = PRIORITY_LEVELS - 1; lvl >= 0 && process == NULL; lvl--)
		if (!is_empty(scheduler->levels[lvl]))
			process = (process_t *) (get_first(scheduler->levels[lvl]))->data;

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
		scheduler->remainingQuantum = 0;
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

	scheduler->remainingQuantum--;
	if (!scheduler->qtyProcesses || scheduler->remainingQuantum > 0)
		return prevStackPointer;

	process_ptr currentProcess;
	node_ptr currentProcessNode = scheduler->processes[scheduler->currentPid];

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

	scheduler->currentPid = get_next_pid(scheduler);
	currentProcess = scheduler->processes[scheduler->currentPid]->data;

	if (scheduler->killFgProcess && currentProcess->fileDescriptors[STDIN] == STDIN) {
		scheduler->killFgProcess = 0;
		if (kill_current_process(-1) != -1)
			forceTimerTick();
	}
	scheduler->remainingQuantum = (MAX_PRIORITY - currentProcess->priority);
	currentProcess->status = RUNNING;
	return currentProcess->stack_position;
}

int16_t createProcess(function_t code, char **args, char *name, uint8_t priority, int16_t fileDescriptors[], uint8_t unkillable) {
	scheduler_ptr scheduler = get_scheduler();
	if (scheduler->qtyProcesses >= MAX_PROCESSES) // TODO: Agregar panic?
		return -1;
	process_ptr process = (process_ptr) mem_alloc(sizeof(process_t));
	initProcess(process, scheduler->nextUnusedPid, scheduler->currentPid, code, args, name, priority, fileDescriptors, unkillable);

	node_ptr processNode;
	if (process->pid != IDLE_PID)
		processNode = add(scheduler->levels[process->priority], (void *) process);
	else {
		processNode = mem_alloc(sizeof(node_t));
		processNode->data = (void *) process;
	}
	scheduler->processes[process->pid] = processNode;

	while (scheduler->processes[scheduler->nextUnusedPid] != NULL)
		scheduler->nextUnusedPid = (scheduler->nextUnusedPid + 1) % MAX_PROCESSES;
	scheduler->qtyProcesses++;
	return process->pid;
}

static void destroyZombie(scheduler_ptr scheduler, process_ptr zombie) {
	node_ptr zombieNode = scheduler->processes[zombie->pid];
	scheduler->qtyProcesses--;
	scheduler->processes[zombie->pid] = NULL;
	free_process(zombie);
	free(zombieNode);
}

int32_t kill_current_process(int32_t ret_value) {
	scheduler_ptr scheduler = get_scheduler();
	return kill_process(scheduler->currentPid, ret_value);
}

int32_t kill_process(uint16_t pid, int32_t ret_value) {
	scheduler_ptr scheduler = get_scheduler();
	node_ptr pnode_to_kill = scheduler->processes[pid];
	if (pnode_to_kill == NULL)
		return -1;
	process_ptr process_to_kill = (process_ptr) pnode_to_kill->data;
	if (process_to_kill->status == ZOMBIE || process_to_kill->unkillable)
		return -1;

	closeFileDescriptors(process_to_kill);

	uint8_t priorityIndex = process_to_kill->status != BLOCKED ? process_to_kill->priority : BLOCKED_INDEX;
	remove_node(scheduler->levels[priorityIndex], pnode_to_kill);
	process_to_kill->ret_value = ret_value;

	process_to_kill->status = ZOMBIE;

	to_begin(process_to_kill->zombieChildren);
	while (has_next(process_to_kill->zombieChildren)) {
		destroyZombie(scheduler, (process_ptr) next(process_to_kill->zombieChildren));
	}

	node_ptr parentNode = scheduler->processes[process_to_kill->parentPid];
	if (parentNode != NULL && ((process_ptr) parentNode->data)->status != ZOMBIE) {
		process_ptr parent = (process_ptr) parentNode->data;
		append_node(parent->zombieChildren, pnode_to_kill);
		if (processIsWaiting(parent, process_to_kill->pid))
			setStatus(process_to_kill->parentPid, READY);
	}
	else {
		destroyZombie(scheduler, process_to_kill);
	}
	if (pid == scheduler->currentPid)
		yield();
	return 0;
}

uint16_t getpid() {
	scheduler_ptr scheduler = get_scheduler();
	return scheduler->currentPid;
}

psnapshotList_ptr getProcessSnapshot() {
	scheduler_ptr scheduler = get_scheduler();
	psnapshotList_ptr snapshotsArray = mem_alloc(sizeof(psnapshotList_t));
	psnapshot_ptr psArray = mem_alloc(scheduler->qtyProcesses * sizeof(psnapshot_t));
	int processIndex = 0;

	loadSnapshot(&psArray[processIndex++], (process_ptr) scheduler->processes[IDLE_PID]->data);
	for (int lvl = PRIORITY_LEVELS; lvl >= 0; lvl--) { // Se cuentan tambien los bloqueados
		begin(scheduler->levels[lvl]);
		while (hasNext(scheduler->levels[lvl])) {
			process_ptr nextProcess = (process_ptr) next(scheduler->levels[lvl]);
			loadSnapshot(&psArray[processIndex], nextProcess);
			processIndex++;
			if (nextProcess->status != ZOMBIE) {
				getZombiesSnapshots(processIndex, psArray, nextProcess);
				processIndex += getLength(nextProcess->zombieChildren);
			}
		}
	}
	snapshotsArray->length = scheduler->qtyProcesses;
	snapshotsArray->snapshotList = psArray;
	return snapshotsArray;
}

int32_t get_zombie_ret_value(uint16_t pid) {
	scheduler_ptr scheduler = get_scheduler();
	node_ptr zombieNode = scheduler->processes[pid];
	if (zombieNode == NULL)
		return -1;
	process_ptr zombieProcess = (process_ptr) zombieNode->data;
	if (zombieProcess->parentPid != scheduler->currentPid)
		return -1;

	process_ptr parent = (process_ptr) scheduler->processes[scheduler->currentPid]->data;
	parent->waitingForPid = pid;
	if (zombieProcess->status != ZOMBIE) {
		setStatus(parent->pid, BLOCKED);
		yield();
	}
	remove_node(parent->zombieChildren, zombieNode);
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
	scheduler->remainingQuantum = 0;
	forceTimerTick();
}

int8_t change_fd(uint16_t pid, uint8_t position, int16_t new_fd) {
	scheduler_ptr scheduler = get_scheduler();
	node_ptr processNode = scheduler->processes[pid];
	if (pid == IDLE_PID || processNode == NULL)
		return -1;
	process_ptr process = (process_ptr) processNode->data;
	process->fileDescriptors[position] = new_fd;
	return 0;
}

int16_t get_current_pfd(uint8_t fd_i) {
	scheduler_ptr scheduler = get_scheduler();
	process_ptr process = scheduler->processes[scheduler->currentPid]->data;
	return process->fileDescriptors[fd_i];
}

void kill_foreground_p() {
	scheduler_ptr scheduler = get_scheduler();
	scheduler->killFgProcess = 1;
}