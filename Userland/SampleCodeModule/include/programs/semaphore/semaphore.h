#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_

#define MAX_SEMAPHORES 15
#define MAX_BLOCKED_PROCESSES 10

typedef struct sem * sem_ptr;

typedef struct copy_sem
{
    char name[40];
    int value;
    int lock;
    int blocked_processes[MAX_BLOCKED_PROCESSES];
} copy_sem_t;

#endif