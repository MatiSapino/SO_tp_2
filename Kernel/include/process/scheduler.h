#ifndef _SCHEDULER_H
#define _SCHEDULER_H
#include <process.h>
#include <stdint.h>

#define MAX_PROCESSES_AMOUNT (1 << 12)
#define PRIORITY_LEVELS 5

typedef struct scheduler {
	node_ptr processes[MAX_PROCESSES_AMOUNT];
	list_ptr levels[PRIORITY_LEVELS + 1];
	uint16_t currentPid;
	uint16_t nextUnusedPid;
	uint16_t qtyProcesses;
	int8_t remainingQuantum;
	int8_t killFgProcess;
}scheduler_t, *scheduler_ptr;

scheduler_ptr create_scheduler();
int16_t create_process(function_t code, char **args, char *name, uint8_t priority, int16_t fds[], uint8_t unkillable);
int32_t kill_process(uint16_t pid, int32_t ret_value);
int32_t kill_current_process(int32_t ret_value);
uint16_t getpid();
pstatus_t get_pstatus(uint16_t pid);
psnapshotList_t *get_psnapshot();
int32_t set_priority(uint16_t pid, uint8_t new_priority);
int8_t set_pstatus(uint16_t pid, uint8_t new_status);
int32_t get_zombie_ret_value(uint16_t pid);
int32_t p_still_alive(uint16_t pid);
void yield();
int8_t change_fd(uint16_t pid, uint8_t position, int16_t new_fd);
int16_t get_current_pfd(uint8_t fd_i);
void kill_foreground_p();
#endif