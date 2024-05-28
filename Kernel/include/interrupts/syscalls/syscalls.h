#ifndef _SYSCALLS_H
#define _SYSCALLS_H

#include <videoDriver.h>
#include <keyboard_buffer.h>
#include <interrupts.h>
#include <process.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

void sys_write(char *buf, int len, int filedescriptor);
void sys_read(char *buf, int len, int filedescriptor);

void sys_close(unsigned int fd);
void sys_exit(int error_code);

#endif // _KEYBOARD_H_