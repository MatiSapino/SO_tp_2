#ifndef _SYSCALLS_H
#define _SYSCALLS_H

#include <videoDriver.h>
#include <keyboard_buffer.h>
#include <interrupts.h>
#include <process.h>
#include <scheduler.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

void sys_write(char *buf, int len, int filedescriptor);
void sys_read(char *buf, int len, int filedescriptor);

void sys_close(unsigned int fd);
void sys_exit(int error_code);

int sys_run(void *main, int argc, char *argv[]);
int sys_block(int pid);
int sys_unblock(int pid);
int sys_get_proc_status(int pid);
int sys_set_priority(int pid, int priority);
int sys_getpid();

#endif // _KEYBOARD_H_