// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <std_io.h>
#include <stdint.h>
#include <testprio.h>
#include <testUtil.h>

#define MINOR_WAIT                                                             \
    1000000 // Change this value to prevent a process from flooding the screen
#define WAIT                                                                   \
    10000000 // TChange this value to make the wait long enough to see theese
             // processes beeing run at least twice

#define TOTAL_PROCESSES 10
#define LOWEST          1  // Change as required
#define MEDIUM          5  // Change as required
#define HIGHEST         10 // Change as required

int64_t prio[TOTAL_PROCESSES] = {LOWEST, MEDIUM, HIGHEST};

int test_prio(int argc, char *argv[]) {
    int64_t pids[TOTAL_PROCESSES];
    char *args[] = {"test-prio"};
    uint64_t i;

    for (i = 0; i < TOTAL_PROCESSES; i++){
        pids[i] = call_run(endless_loop, 1, args);
        own_printf("\nCREATING PROCESS WITH PID: %d...\n", pids[i]);
    }

    bussy_wait(WAIT);

    for (i = 0; i < TOTAL_PROCESSES; i++){
        call_set_priority(pids[i], prio[i]);
        own_printf("\nCHANGING PRIORITY FOR PID: %d TO %d...\n", pids[i], prio[i]);
    }

    for (i = 0; i < TOTAL_PROCESSES; i++){
        call_block(pids[i]);
        own_printf("\nBLOCKING PID: %d...\n", pids[i]);
    }

    for (i = 0; i < TOTAL_PROCESSES; i++){
        call_set_priority(pids[i], MEDIUM);
        own_printf("\nCHANGING PRIORITY FOR PID: %d TO %d...\n", pids[i], MEDIUM);
    }

    for (i = 0; i < TOTAL_PROCESSES; i++){
        call_unblock(pids[i]);
        own_printf("\nUNBLOCKING PID: %d...\n", pids[i]);
    }

    for (i = 0; i < TOTAL_PROCESSES; i++) {
        call_kill(pids[i]);
        own_printf("\nKILLING PID: %d...\n", pids[i]);
        call_wait();
    }
    return 0;
}