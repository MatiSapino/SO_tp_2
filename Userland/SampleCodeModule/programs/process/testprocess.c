// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <std_io.h>
#include <testprocess.h>
#include <testUtil.h>
#include <help.h>

typedef struct P_rq {
    int pid;
    pstatus_t state;
} p_rq;

int test_proc(int argc, char *argv[]) {
    int flag = 0;
    uint8_t rq;
    uint8_t alive = 0;
    uint8_t action;
    uint64_t max_processes = satoi(argv[1]);
    char *argvAux[] = {"test-proc"};

    if (argc != 2){
        own_printf("argument amount is incorrect\n");
        flag++;
    } else if (max_processes <= 0){ 
        own_printf("process amount value is not valid - process amount must be a positive number\n\n");
        flag++;
    }

    if (flag > 0){
        help_testproc();
        return -1;
    }

    p_rq p_rqs[max_processes];

    while (1) {

        // Create max_processes processes
        for (rq = 0; rq < max_processes; rq++) {
            p_rqs[rq].pid = call_run(endless_loop, 1, argvAux);

            if (p_rqs[rq].pid == -1) {
                own_printf("test_processes: ERROR creating process\n");
                return -1;
            } else {
                own_printf("pid: %d Created and Ready\n", p_rqs[rq].pid);
                p_rqs[rq].state = READY;
                alive++;
            }
        }

        // Randomly kills, blocks or unblocks processes until every one has been
        // killed
        while (alive > 0) {

            for (rq = 0; rq < max_processes; rq++) {
                action = GetUniform(100) % 2;

                switch (action) {
                    case 0:
                        if (p_rqs[rq].state == READY ||
                            p_rqs[rq].state == WAITING) {
                            if (call_kill(p_rqs[rq].pid) == -1) {
                                own_printf(
                                    "test_processes: ERROR killing process\n");
                                return -1;
                            }
                            own_printf("pid: %d Killed\n", p_rqs[rq].pid);
                            call_wait();
                            p_rqs[rq].state = TERMINATED;
                            alive--;
                        }
                        break;

                    case 1:
                        if (p_rqs[rq].state == READY) {
                            if (call_block(p_rqs[rq].pid) == -1) {
                                own_printf(
                                    "test_processes: ERROR blocking process\n");
                                return -1;
                            }
                            own_printf("pid: %d Waiting\n", p_rqs[rq].pid);
                            p_rqs[rq].state = WAITING;
                        }
                        break;
                }
            }

            // Randomly unblocks processes
            for (rq = 0; rq < max_processes; rq++)
                if (p_rqs[rq].state == WAITING && GetUniform(100) % 2) {
                    if (call_unblock(p_rqs[rq].pid) == -1) {
                        own_printf(
                            "test_processes: ERROR unblocking process\n");
                        return -1;
                    }
                    own_printf("pid: %d Ready\n", p_rqs[rq].pid);

                    p_rqs[rq].state = READY;
                }
        }
    }
    return 0;
}