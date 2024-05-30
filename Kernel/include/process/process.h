#ifndef _PROCESS_H_
#define _PROCESS_H_

#include <memory_manager.h>
#include <dataDescriptor.h>
#include <string_s.h>
#include <linkedList.h>

#define P_INIT_EFLAGS 0x202
#define P_INIT_CS 0x8
#define P_SS 0
#define P_EXIT_CODE 0
#define PROCESS_COMUNICATION_AMOUNT 128

#define LOWEST 1
#define MEDIUM 5
#define HIGHEST 10

#define K_PROCESS_STACK_SIZE (1024 * 4)

typedef enum pstatus {
    BLOCKED = 0,
    READY,
    RUNNING,
    ZOMBIE,
    DEAD 
} pstatus_t;

typedef uint16_t pid_t;

typedef struct context {
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

    uint64_t rip;
    uint64_t cs;
    uint64_t eflags;
    uint64_t rsp;
    uint64_t ss;
} context_t, *context_ptr;

typedef struct process {
    char *name;
    pid_t pid;
    pid_t parent_pid;
    context_ptr context;
    pstatus_t status;
    data_descriptor_ptr data_descriptors[PROCESS_COMUNICATION_AMOUNT];
    size_t data_d_index;
    void *channel;
    list_ptr children;
    list_ptr zombies;
    int ret_value;
    int exit_status;
    int priority;
    char **argv;
    int argc;
    void *stack_base;
    void *stack_position;
} process_t, *process_ptr;

typedef struct psnapshot {
	uint16_t pid;
	uint16_t parentPid;
	void *stackBase;
	void *stackPos;
	char *name;
	uint8_t priority;
	pstatus_t status;
	uint8_t foreground;
} psnapshot_t, *psnapshot_ptr;

typedef struct psnapshotList {
	uint16_t length;
	psnapshot_t *snapshotList;
} psnapshotList_t, *psnapshotList_ptr;

typedef int (*function_t)(int, char *[]);

void p_init(process_ptr process, uint16_t pid, uint16_t parent_pid, function_t code, int argc, char *argv[], char *name, uint8_t priority, int16_t fds[]);

void free_process(process_t *process);

static int search_by_pid(void *process, void *pid);

#endif