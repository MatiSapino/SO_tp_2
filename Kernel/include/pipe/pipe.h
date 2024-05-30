#ifndef _PIPE_H_
#define _PIPE_H_

#include <stdint.h>
#include <string_s.h>
#include <linkedList.h>

#define PIPE_SIZE (1024)


typedef struct pipe {
    char *name;
    unsigned int nwrite;
    unsigned int nread;
    int readopen;
    int writeopen;
    list_ptr blocked_pid;
} pipe_t, *pipe_ptr;


/**   
 * @retval 0 on success. -1 if pipe have been already initialized 
 */
int init_pipes();

/**   
 * @retval 0 on success. -1 if the pipe have been already created or the pipe can´t be created
 */
pipe_ptr create_pipe(char * name, int pipe_dataD[2]);

/**   
 * @retval 0 on success. -1 if pipes have not been initialized or there is not pipe with the name given
 */
int open_pipe(char * name , int pipe_dataD[2]);

/**   
 * @retval the number of bytes readed on success. -1 in error
 */
int piperead(pipe_ptr pipe, char * buffer, int count);

int pipewrite(pipe_ptr pipe, const char * buffer, int count);

void close_pipe(pipe_ptr pipe, int writable);

int info_pipe(char * name, pipe_ptr info);

int info_all_pipes(pipe_ptr  info_arr[], unsigned int size);

void add_writer(pipe_ptr pipe);

void add_reader(pipe_ptr pipe);

#endif