#ifndef _MY_SEM_H_
#define _MY_SEM_H_

#include <linked_list.h> 

#define MAX_SEM_VALUE 5
#define MAX_SEMAPHORES 100

typedef struct sem {
    char name[40];
    int value;
    int lock;
    list_ptr blocked_processes;
} sem_t;

typedef struct copy_sem {
    char name[40];
    int value;
    int lock;
    int blocked_processes[];
} copy_sem_t;

typedef sem_t * sem_ptr;
typedef copy_sem_t * copy_sem_ptr;

void init_sem_list();
sem_ptr sem_open(char *, int value);
int sem_wait(sem_ptr semaphore);
int sem_post(sem_ptr semaphore);
int sem_close(sem_ptr semaphore);
int get_semaphores(copy_sem_ptr sems[]);

#endif
