#ifndef _DATADESCRIPTOR_H_
#define _DATADESCRIPTOR_H_

#include <stdbool.h>
#include <pipe/pipe.h>

typedef struct dataDescriptor * dataDescriptor_t;
typedef enum  {STD_T, PIPE_T} DATA_TYPE;
typedef enum  {READ_MODE, WRITE_MODE} mode_t;

dataDescriptor_t create_dataDescriptor(DATA_TYPE type , mode_t mode);
int setPipe_dataDescriptor(dataDescriptor_t dataD ,pipe_t pipe);
pipe_t getPipe_dataDescriptor(dataDescriptor_t dataD);
DATA_TYPE getDataType_dataDescriptor(dataDescriptor_t dataD);
mode_t getMode_dataDescriptor(dataDescriptor_t dataD);
void close_dataDescriptor(dataDescriptor_t dataD);
int dup2(unsigned int oldfd , unsigned int newfd);

#endif