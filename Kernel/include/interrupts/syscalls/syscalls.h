#ifndef _SYSCALLS_H_
#define _SYSCALLS_H_

#include <registers.h>
#include <rtc.h>
#include <stddef.h>
#include <stdint.h>

#define ERROR   -1
#define SUCCESS 0

enum STD {
    STDIN,
    STDOUT,
    STDERR
};

typedef struct sem *sem_ptr;
typedef struct copy_sem copy_sem_t;
typedef struct pipe_info pipe_info_t;
typedef struct process_table process_table_t;

int16_t sys_read(int fd, char *buffer, uint16_t count);
int16_t sys_write(int fd, char *buffer, uint16_t count);
uint8_t sys_gettime(time_rtc_t *struct_time, int utc_offset);
void sys_exit(int error_code);
void sys_switch_screen_mode(int mode);
int sys_copy_cpu_state(cpu_state_t *cpu_ptr, request_t request);
void sys_clear_screen();
uint8_t sys_cntrl_listener(uint8_t *listener);
void sys_delete_char();
int sys_run(void *main, int argc, char *argv[]);
int sys_wait();
int sys_kill(int pid);
uint16_t sys_get_mem(uint8_t *address, uint8_t *buffer, uint16_t count);
void sys_get_mem_state(int mem_state[]);
int sys_get_proc_status(int pid);
int sys_block(int pid);
int sys_unblock(int pid);
void sys_focus(int pid);
void sys_sched_yield();
int sys_waitpid(int pid, int *status_ptr);
sem_ptr sys_sem_open(char *name, int value);
int sys_sem_wait(sem_ptr sem);
int sys_sem_post(sem_ptr sem);
int sys_sem_close(sem_ptr sem);
int sys_get_semaphores(copy_sem_t *sems[]);
void *sys_malloc(size_t size);
void sys_free(void *ptr);
void sys_close(unsigned int fd);
int sys_create_pipe(char *name, int fd[2]);
int sys_open_pipe(char *name, int fd[2]);
int sys_info_pipe(char *name, pipe_info_t *info);
int sys_info_all_pipes(pipe_info_t *info[], unsigned int size);
int sys_dup2(unsigned int oldfd, unsigned int newfd);
void sys_setfg(int pid);
int sys_getpid();
int sys_set_priority(int pid, int priority);
void sys_proctable(process_table_t *table);
void sys_sleep(int seconds);

#endif