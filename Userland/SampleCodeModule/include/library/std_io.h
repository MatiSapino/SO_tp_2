#ifndef _STD_IO_H_
#define _STD_IO_H_

#include <colors.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <shell.h>
#include <std_lib.h>
#include <string_s.h>
#include <utils.h>

#include <UserSyscalls.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

typedef enum chld {
    LEFT_CHD = 0,
    RIGHT_CHD
} chld_t;

typedef enum pstatus {
    WAITING = 0,
    READY,
    TERMINATED,
} pstatus_t;

char getC();
void putC(char c, int color);
void putNewLine();
void putString(char *str, int color);
void putInt(int num);
void putIntColor(int num, int color);
void own_printf(const char *format, ...);
int own_scanf(char *format, ...);
int readInt(int *d);
int readString(char *s);
int readHexInt(int *d);

void call_close(unsigned int fd);
int call_get_mem(uint8_t *address, uint8_t *buffer, size_t count);
void call_sched_yield();
void call_setfg(int pid);

int call_run(void *main, int argc, char *argv[]);
int call_exit(int error_code);
int call_wait();
int call_waitpid(int pid, int *status_ptr);
int call_kill(int pid);
int call_block(int pid);
int call_unblock(int pid);
int call_get_proc_status(int pid);
int call_set_priority(int pid, int priority);
int call_sleep_process(int seconds);
int call_getpid();

#endif