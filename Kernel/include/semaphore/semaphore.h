#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_

#include <linkedList.h>
#include <string_s.h>
#include <memory_manager.h>
#include <process.h>

#define MAX_SEM_VALUE 5
#define MAX_SEMAPHORES 100
#define ERROR -1
#define SUCCESS 0

typedef struct sem
{
    char name[40];
    int value;
    int lock;
    list_ptr blocked_processes;
} sem_t;

// typedef struct copy_sem
// {
//     char name[40];
//     int value;
//     int lock;
//     int blocked_processes[];
// } copy_sem_t;

typedef struct sem *sem_ptr;
typedef struct copy_sem copy_sem_t;

void init_sem_list();
sem_ptr sem_open(char *, int value);
int sem_wait(sem_ptr semaphore);
int sem_post(sem_ptr semaphore);
int sem_close(sem_ptr semaphore);
int get_semaphores(copy_sem_t *sems[]);

extern int xadd(int *var_ptr, int value);
extern int xchg(int *var_ptr, int value);

#endif