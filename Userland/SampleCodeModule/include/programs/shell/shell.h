#ifndef __SHELL_H__
#define __SHELL_H__

#include <std_io.h>
#include <screen.h>
#include <buffer.h>

int start_shell();
void changeStatus();
void showScreen();
void clearScreenArray();
void putIntoScreen();

#endif