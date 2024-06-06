#ifndef _PIPE_H_
#define _PIPE_H_

typedef struct pipe_info{
    char * name;
    unsigned int nwrite;
    unsigned int nread;
    int readopen;
    int writeopen;
    int blocked_pid[64];
    int blocked_count;
} pipe_info_t;

int call_create_pipe(char * name, int fd[2]);
int call_open_pipe(char * name, int fd[2]);
int call_info_pipe(char * name, pipe_info_t * info);
int call_info_all_pipes(pipe_info_t * info[] , unsigned int size);
int call_dup2(unsigned int oldfd , unsigned int newfd);

#endif 