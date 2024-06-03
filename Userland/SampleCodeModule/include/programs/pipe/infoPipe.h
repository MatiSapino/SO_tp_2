#ifndef _INFO_PIPE
#define _INFO_PIPE_

#include <std_io.h>
#include <string_s.h>
#include <std_lib.h>
#include <pipe.h>

typedef struct pipe_info{
    char * name;
    unsigned int nwrite;
    unsigned int nread;
    int readopen;
    int writeopen;
    int blocked_pid[64];
    int blocked_count;
} pipe_info_t;

#define MAX_PIPES 32

void info_pipe(char *name);
int info_all_pipes(int argc, char *argv[]);

#endif