// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <std_io.h>
#include <testsync.h>
#include <testUtil.h>
#include <userland_semaphore.h>

#define SEM_ID               "sem"
#define TOTAL_PAIR_PROCESSES 2

int64_t global = 0;        // shared memory
sem_ptr global_sem = NULL; // used to close semaphore from test_sync

void slowInc(int64_t *p, int inc) {
    uint64_t aux = *p;
    call_sched_yield(); // This makes the race condition highly probable
    aux += inc;
    *p = aux;
}

int myprocinc(int argc, char *argv[]) {
    uint64_t n;
    int8_t inc;
    int8_t use_sem;
    sem_ptr sem = NULL;

    if (argc != 4)
        return -1;

    if ((n = satoi(argv[1])) <= 0)
        return -1;
    if ((inc = satoi(argv[2])) == 0)
        return -1;
    if ((use_sem = satoi(argv[3])) < 0)
        return -1;

    if (use_sem)
        if (!(sem = call_sem_open(SEM_ID, 1))) {
            own_printf("test_sync: error opening semaphore\n");
            return -1;
        }

    uint64_t i;
    for (i = 0; i < n; i++) {
        if (use_sem)
            call_sem_wait(sem);
        slowInc(&global, inc);
        if (use_sem)
            call_sem_post(sem);
    }

    if (use_sem)
        global_sem = sem;

    return 0;
}

int test_sync(int argc, char *argv[]) { //{n, use_sem, 0}

    if (argc < 3) {
        own_printf("test_sync: missing arguments\n");
        return -1;
    }

    if (argc > 3) {
        own_printf("test_sync: too many arguments\n");
        return -1;
    }

    if (satoi(argv[1]) <= 0) {
        own_printf("test_sync: increment is not a valid argument\n");
        return -1;
    }

    if (satoi(argv[2]) < 0) {
        own_printf("test_sync: use_sem is not a valid argument\n");
        return -1;
    }

    int exit_status;
    int pids[2 * TOTAL_PAIR_PROCESSES];
    global = 0;

    char *argvDec[] = {"myprocinc", argv[1], "-1", argv[2]};
    char *argvInc[] = {"myprocinc", argv[1], "1", argv[2]};

    uint64_t i;
    for (i = 0; i < TOTAL_PAIR_PROCESSES; i++) {
        pids[i] = call_run(myprocinc, 4, argvDec);
        pids[i + TOTAL_PAIR_PROCESSES] = call_run(myprocinc, 4, argvInc);
    }

    for (i = 0; i < TOTAL_PAIR_PROCESSES; i++) {
        call_waitpid(pids[i], &exit_status);
        call_waitpid(pids[i + TOTAL_PAIR_PROCESSES], &exit_status);
    }

    if (satoi(argv[2]) > 0)
        call_sem_close(global_sem);

    own_printf("testsync: final value: %d\n", global);

    return 0;
}