#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

#include <process.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_PROC_COUNT         256
#define MAX_NAME_LENGTH        10
#define PROCESS_TABLE_MAX_SIZE 16

typedef struct process_entry {
    int pid;
    char name[MAX_NAME_LENGTH];
    int priority;
    void *stack;
    uint64_t rbp;
    int children_count;
    char parent_name[MAX_NAME_LENGTH];
    int status;
} process_entry_t;

typedef struct process_table {
    process_entry_t entries[PROCESS_TABLE_MAX_SIZE];
    int count;
} process_table_t;

pid_t wait_process(pid_t pid, int *status_ptr);

extern void _force_schedule();

context_t *schedule(context_t *rsp);
int add_process(function_t main, int argc, char *argv[]);
void exit_process(int status);
int kill_process(pid_t pid);
process_t *get_current_process();
process_t *get_process(pid_t pid);
process_t *get_foreground_process();
void set_foreground_process(int pid);
void sleep(void * channel);
int wakeup(void * channel);
void init_scheduler();
int get_process_table(process_table_t *table);
int search_by_status(void *process, void *status);

#endif