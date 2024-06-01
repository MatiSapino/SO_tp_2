#ifndef _PROCESS_H_
#define _PROCESS_H_

#include <globals.h>

#define MAX_NAME_LENGTH        10
#define PROCESS_TABLE_MAX_SIZE 16

typedef struct process_entry {
    int pid;
    char name[MAX_NAME_LENGTH];
    int priority;
    void *stack;
    void *rbp;
    int children_count;
    char parent_name[MAX_NAME_LENGTH];
    int status;
} process_entry_t;

typedef struct process_table {
    process_entry_t entries[PROCESS_TABLE_MAX_SIZE];
    int count;
} process_table_t;


int call_get_process_table(process_table_t *table);
int call_run(void *main, int argc, char *argv[]);
int call_kill(int pid);
int call_wait();
int call_block(int pid);
int call_unblock(int pid);
int call_exit(int error_code);
int call_waitpid(int pid, int *status_ptr);
int call_get_proc_status(int pid);
int call_set_priority(int pid, int priority);
int call_sleep(int seconds);
int call_getpid();

#endif