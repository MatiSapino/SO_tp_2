#ifndef _USERLAND_SEMAPHORE_H_
#define _USERLAND_SEMAPHORE_H_

#define MAX_SEMAPHORES        15
#define MAX_BLOCKED_PROCESSES 10
#include <userland_linked_list.h>

typedef struct sem {
    char name[40];
    int value;
    int lock;
    list_ptr blocked_processes;
} sem_t;

typedef sem_t * sem_ptr;

typedef struct copy_sem {
    char name[40];
    int value;
    int lock;
    int blocked_processes[MAX_BLOCKED_PROCESSES];
} copy_sem_t;

sem_ptr call_sem_open(char *name, int value);
int call_sem_wait(sem_ptr sem);
int call_sem_post(sem_ptr sem);
int call_sem_close(sem_ptr sem);
int call_get_semaphores(copy_sem_t *sems[]);

#endif