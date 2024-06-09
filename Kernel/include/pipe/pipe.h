#ifndef _PIPE_H_
#define _PIPE_H_

#include <linked_list.h> 


#define PIPE_SIZE (1024)

typedef struct pipe {
    char *name;
    char data[PIPE_SIZE];
    unsigned int nwrite;
    unsigned int nread;
    int readopen;
    int writeopen;
    list_ptr blocked_pid;
} pipe_t;
typedef pipe_t * pipe_ptr;

typedef struct pipe_info {
    char *name;
    unsigned int nwrite;
    unsigned int nread;
    int readopen;
    int writeopen;
    int blocked_pid[64];
    int blocked_count;
} pipe_info_t;
typedef pipe_info_t * pipe_info_ptr;

int init_pipes();
int create_pipe(char * name, int pipe_dataD[2]);
int open_pipe(char * name , int pipe_dataD[2]);
int piperead(pipe_ptr pipe, char *buffer, int count);
int pipewrite(pipe_ptr pipe, const char *buffer, int count);
void close_pipe(pipe_ptr pipe, int writable);
int info_pipe(char * name, pipe_info_t * info);
int info_all_pipes( pipe_info_t * info_arr[], unsigned int size);
void add_writer(pipe_ptr pipe);
void add_reader(pipe_ptr pipe);

#endif
