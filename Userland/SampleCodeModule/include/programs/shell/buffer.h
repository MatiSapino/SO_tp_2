#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <screen.h>
#include <colors.h>

#define STDIN 0
#define BUFFER_SIZE 128

static char buffer[BUFFER_SIZE] = {0};

void clearBuffer(char *buff);
void read_buffer(int screenIndx, char screen[SCREEN_SIZE], char buffer[BUFFER_SIZE], int status);

#endif