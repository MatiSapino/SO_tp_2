#ifndef _STD_IO_H_
#define _STD_IO_H_

#include <stddef.h>
#include <stdint.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

#define REG_SIZE        16
#define REGISTERS_COUNT 18

typedef enum chld {
    LEFT_CHD = 0,
    RIGHT_CHD
} chld_t;

typedef struct time {
    uint64_t year;
    uint64_t month;
    uint64_t day;
    uint64_t hour;
    uint64_t minutes;
    uint64_t seconds;
} time_rtc_t;

typedef struct cpu_state {
    uint64_t rsp;
    uint64_t rflags;
    uint64_t rip;

    uint64_t r15;
    uint64_t r14;
    uint64_t r13;
    uint64_t r12;
    uint64_t r11;
    uint64_t r10;
    uint64_t r9;
    uint64_t r8;

    uint64_t rsi;
    uint64_t rdi;
    uint64_t rbp;

    uint64_t rdx;
    uint64_t rcx;
    uint64_t rbx;
    uint64_t rax;
} cpu_state_t;

typedef enum {
    KBD_PRINT_REG = 1
} request_t;

typedef enum pstatus {
    WAITING = 0,
    READY,
    TERMINATED,
} pstatus_t;

int call_read(int fd, char *buffer, size_t count);
int call_write(int fd, char *buffer, size_t count);
int call_clear_screen();
int call_time(time_rtc_t *time_struct, int utc_offset);
int call_cntrl_pressed();
int call_copy_cpu_state(cpu_state_t *cpu_ptr, request_t request);
void call_delete_char();
int call_cntrl_listener(char *listener);
void call_focus(int pid);
void call_setfg(int pid);

void call_close(unsigned int fd);
int call_get_mem(uint8_t *address, uint8_t *buffer, size_t count);
void call_sched_yield();

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

int call_switch_screen_mode(int mode);

int getchar();
int putchar(int character);
int puts(const char *str);

int own_printf(char *str, ...);
int own_scanf(char *str, ...);
void call_new_line();


char call_get_last_key();
void call_clear_buffer();

#endif