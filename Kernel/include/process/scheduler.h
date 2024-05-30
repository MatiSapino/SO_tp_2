#ifndef _SCHEDULER_H
#define _SCHEDULER_H
#include <process.h>
#include <stdint.h>

#define MAX_PROCESSES_AMOUNT (1 << 12)
#define PRIORITY_LEVELS 5

typedef struct scheduler {
	node_ptr processes[MAX_PROCESSES_AMOUNT];
	list_ptr levels[PRIORITY_LEVELS + 1];
	uint16_t pid;
	uint16_t next_available_pid;
	uint16_t process_amount;
	int8_t quantums_left;
	int8_t kill_foreground_p;
}scheduler_t, *scheduler_ptr;

scheduler_ptr create_scheduler();
int16_t create_process(function_t code, int argc, char **argv, char *name, uint8_t priority, int16_t fds[], uint8_t is_init);
int32_t kill_process(uint16_t pid, int32_t ret_value);
int32_t kill_current_process(int32_t ret_value);
uint16_t getpid();
pstatus_t get_pstatus(uint16_t pid);
psnapshot_ptr * get_psnapshot();
int32_t set_priority(uint16_t pid, uint8_t new_priority);
int8_t set_pstatus(uint16_t pid, uint8_t new_status);
int32_t get_zombie_ret_value(uint16_t pid);
int32_t p_still_alive(uint16_t pid);
void yield();
int8_t change_fd(uint16_t pid, uint8_t std, int16_t new_fd);
int16_t get_current_p_fd(uint8_t std);
void kill_foreground_p();
int search_by_pid(void *process, void *pid);

#endif