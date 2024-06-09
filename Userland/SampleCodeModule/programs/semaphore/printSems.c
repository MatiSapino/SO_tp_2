#include <mem.h>
#include <userland_semaphore.h>
#include <std_io.h>
#include <printSems.h>

int printsems(int argc, char *argv[]) {

    copy_sem_t *copied_sems[MAX_SEMAPHORES];

    for (int i = 0; i < MAX_SEMAPHORES; i++) {
        copied_sems[i] = (copy_sem_t *)call_malloc(sizeof(copy_sem_t));
        for (int k = 0; k < MAX_BLOCKED_PROCESSES; k++) {
            copied_sems[i]->blocked_processes[k] = 0;
        }
    }

    int i = call_get_semaphores(copied_sems);
    own_printf("NAME           |  VALUE  | BLOCKED PIDS      \n");
    own_printf("\n");
    copy_sem_t *aux_sem;
    for (int j = 0; j < i; j++) {
        aux_sem = copied_sems[j];
        own_printf("%15s|", aux_sem->name);
        own_printf("  %7d|", aux_sem->value);
        for (int k = 0; aux_sem->blocked_processes[k] > 0; k++) {
            own_printf(" %d", aux_sem->blocked_processes[k]);
        }
        own_printf("\n");
    }

    for (int k = 0; k < MAX_SEMAPHORES; k++) {
        call_free(copied_sems[k]);
    }

    return 0;
}