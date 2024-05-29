#ifndef _PIPE_H_
#define _PIPE_H_

typedef struct pipe_info
{
    char *name;
    unsigned int nwrite;
    unsigned int nread;
    int readopen;
    int writeopen;
    int blocked_pid[64];
    int blocked_count;
} pipe_info_t, *pipe_info_ptr;

#endif