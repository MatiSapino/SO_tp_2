#ifndef _DATA_DESCRIPTOR_H_
#define _DATA_DESCRIPTOR_H_

#include <stdbool.h>
#include <memory_manager.h>
#include <pipe.h>


typedef struct dataDescriptor * dataDescriptor_t;
typedef enum  {STD_T, PIPE_T} DATA_TYPE;
typedef enum  {READ_MODE, WRITE_MODE} mode_t;

typedef struct dataDescriptor {
    DATA_TYPE type;
    mode_t mode;
    pipe_info_ptr pipe_info;
} dataDescriptor_t, * dataDescriptor_ptr;

/**
 * @retval  NULL if the specified type or mode is wrong
 */
dataDescriptor_ptr create_dataDescriptor(DATA_TYPE type , mode_t mode);

/** 
 * @retval 0 on success. -1 if the dataD is not of pipe_info_ptr type
 */
int setPipe_dataDescriptor(dataDescriptor_ptr dataD ,pipe_info_ptr pipe);

/** 
 * @retval NULL if an error ocurred
 */
pipe_info_ptr getPipe_dataDescriptor(dataDescriptor_ptr dataD);

/** 
 * @retval -1 if an error ocurred
 */
DATA_TYPE getDataType_dataDescriptor(dataDescriptor_ptr dataD);

mode_t getMode_dataDescriptor(dataDescriptor_ptr dataD);

void close_dataDescriptor(dataDescriptor_ptr dataD);

//int dup2(unsigned int oldfd , unsigned int newfd);

#endif