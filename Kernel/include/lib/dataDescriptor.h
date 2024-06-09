#ifndef _DATA_DESCRIPTOR_H_
#define _DATA_DESCRIPTOR_H_

#include <stdbool.h>
#include <pipe.h>

typedef enum  {STD_T, PIPE_T} DATA_TYPE;
typedef enum  {READ_MODE, WRITE_MODE} mode_t;

typedef struct data_descriptor {
    DATA_TYPE type;
    mode_t mode;
    pipe_ptr pipe;
} data_descriptor_t;
typedef data_descriptor_t * data_descriptor_ptr;

data_descriptor_ptr create_dataDescriptor(DATA_TYPE type , mode_t mode);
int setPipe_dataDescriptor(data_descriptor_ptr dataD, pipe_ptr pipe);
pipe_ptr getPipe_dataDescriptor(data_descriptor_ptr dataD);
DATA_TYPE getDataType_dataDescriptor(data_descriptor_ptr dataD);
mode_t getMode_dataDescriptor(data_descriptor_ptr dataD);
void close_dataDescriptor(data_descriptor_ptr dataD);
int dup2(unsigned int oldfd , unsigned int newfd);

#endif