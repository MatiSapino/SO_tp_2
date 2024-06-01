#ifndef _GLOBALS_H_
#define _GLOBALS_H_

typedef enum pstatus {
    WAITING = 0,
    READY,
    TERMINATED,
} pstatus_t;

#ifdef DEFINE_MAX_BLOCKED_PROCESSES
#define BLOCKED_PROCESSES_SIZE MAX_BLOCKED_PROCESSES
#else
#define BLOCKED_PROCESSES_SIZE
#endif

typedef struct copy_sem
{
    char name[40];
    int value;
    int lock;
    int blocked_processes[BLOCKED_PROCESSES_SIZE];
} copy_sem_t;

typedef struct pipe_info{
    char * name;
    unsigned int nwrite;
    unsigned int nread;
    int readopen;
    int writeopen;
    int blocked_pid[64];
    int blocked_count;
} pipe_info_t;

#endif