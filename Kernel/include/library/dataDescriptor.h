#ifndef _DATA_DESCRIPTOR_H_
#define _DATA_DESCRIPTOR_H_

#include <stdbool.h>
#include <memory_manager.h>
#include <../pipe/pipe.h>

typedef enum  {STD_T, PIPE_T} DATA_TYPE;
typedef enum  {READ_MODE, WRITE_MODE} mode_t;

typedef struct data_descriptor {
    DATA_TYPE type;
    mode_t mode;
    pipe_ptr pipe;
} data_descriptor_t, * data_descriptor_ptr;

/**
 * @retval  NULL if the specified type or mode is wrong
 */
data_descriptor_ptr create_data_descriptor(DATA_TYPE type , mode_t mode);

/** 
 * @retval 0 on success. -1 if the dataD is not of pipe_ptr type
 */
int set_pipe(data_descriptor_ptr dataD,pipe_ptr pipe);

/** 
 * @retval NULL if an error ocurred
 */
pipe_ptr get_pipe(data_descriptor_ptr dataD);

/** 
 * @retval -1 if an error ocurred
 */
DATA_TYPE get_data_type(data_descriptor_ptr dataD);

mode_t get_mode(data_descriptor_ptr dataD);

void close(data_descriptor_ptr dataD);

//int dup2(unsigned int oldfd , unsigned int newfd);

#endif