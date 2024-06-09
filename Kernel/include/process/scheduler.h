#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

#include <process.h>

#define MAX_PROC_COUNT         256
#define MAX_NAME_LENGTH        10
#define PROCESS_TABLE_MAX_SIZE 16

typedef struct process_entry {
    pid_t pid;
    char name[MAX_NAME_LENGTH];
    int priority;
    void *stack;
    uint64_t rbp;
    int children_count;
    char parent_name[MAX_NAME_LENGTH];
    int status;
} process_entry_t;
typedef process_entry_t * process_entry_ptr;

typedef struct process_table {
    process_entry_t entries[PROCESS_TABLE_MAX_SIZE];
    int count;
} process_table_t;
typedef process_table_t * process_table_ptr;


pid_t wait_process(pid_t pid, int *status_ptr);

extern void _force_schedule();

context_ptr schedule(context_ptr rsp);
int add_process(function_t main, int argc, char *argv[]);
void exit_process(int status);
int kill_process(pid_t pid);
process_ptr get_current_process();
process_ptr get_process(pid_t pid);
process_ptr get_foreground_process();
void set_foreground_process(int pid);
void sleep(void * channel);
int wakeup(void * channel);
void init_scheduler();
int get_process_table(process_table_ptr table);
int search_by_status(void *process, void *status);

#endif