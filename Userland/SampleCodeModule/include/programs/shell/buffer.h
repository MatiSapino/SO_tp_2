#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <screen.h>
#include <colors.h>
#include <commands.h>

#define BUFFER_SIZE 128

void clearBuffer(char *buff);
void read_buffer(int *screenIndx, char screen[], char buffer[], int *status);

#endif