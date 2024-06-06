#ifndef _PIPE_H_
#define _PIPE_H_

#include <stdlib.h>

typedef struct pipe * pipe_t;
typedef struct pipe_info pipe_info_t;

int init_pipes();
int create_pipe(char * name, int pipe_dataD[2]);
int open_pipe(char * name , int pipe_dataD[2]);
int piperead(pipe_t pipe, char * buffer, int count);
int pipewrite(pipe_t pipe, const char * buffer, int count);
void close_pipe(pipe_t pipe, int writable);
int info_pipe(char * name, pipe_info_t * info);
int info_all_pipes( pipe_info_t * info_arr[], unsigned int size);
void add_writer(pipe_t pipe);
void add_reader(pipe_t pipe);

#endif
