#include "./include/semaphore.h"
#include <circularLinkedList.h>
#include <stdint.h>
#include "../Lib/include/string_s.h"

extern void enter_region(uint64_t *lock, uint64_t sem_idx);                         // estas son funciones en assembler que tengo que hacer
extern void leave_region(uint64_t *lock, uint64_t sem_idx);

typedef struct{
    semaphore sem;
    int status;
} sem_array_slot;

static sem_array_slot semaphore_array[MAX_SEMAPHORES];                           // array of all semaphores with an int indicating if occupied

uint64_t my_sem_up(char* semaphore_name){
    int sem_index = locate_sem(semaphore_name);
    if(sem_index == -1){    
        return -1;                                                               // semaphore not found
    }

    // correr la funcion para desbloquear el proceso por assembler

}

uint64_t my_sem_down(char* semaphore_name){
    int sem_index = locate_sem(semaphore_name);
    if(sem_index == -1){
        return -1;
    }

    // int process_pid = getpid();              // faltaria el getPid() propio


    // falta aca correr la funcion por assembler para bloquear el proceso
}

uint64_t my_sem_open(char* semaphore_name, uint64_t initial_value){
    int sem_index = locate_sem(semaphore_name);
    if(sem_index != -1){                    // semaphore already exists so it puts the process inside the semaphore
        // some stuff
        return sem_index;
    }

    // semaphore does not exist yet
    // have to go through the array until we find an empty place

    for(int i = 0; i < MAX_SEMAPHORES; i++){
        if(semaphore_array[i].status == AVAILABLE){             // find an empty place in the array
            semaphore_array[i].status = OCCUPIED;           
            // setear un semaforo de 0 (crear otra funcion despues que lo haga)
        }

    }

}

uint64_t my_sem_close(char* semaphore_name){
    int sem_index = locate_sem(semaphore_name);
    if(sem_index == -1){
        return -1;                              //  semaphore not found
    }

    semaphore *aux_sem = &(semaphore_array[sem_index].sem);
    int current_pid;
    // int current_pid = getpid(); // falta el getpid();

    for(int i = 0; i <aux_sem->process_count; i++) {                // searches for the process inside the semaphore and removes it
        if(aux_sem->processes[i] == current_pid){
            aux_sem->processes[i] = -1;
            aux_sem->process_count--;
        }
    }

    if(aux_sem->process_count == 0){
        // aca deberia cerrar el semaforo y liberar toda la memoria
    }
}

void initailize_sems(){                                 
    for(int i=0; i < MAX_SEMAPHORES; i++){
        semaphore_array[i].status = AVAILABLE;
        for(int j=0; j < MAX_PROCESSES; j++){
            semaphore_array[i].sem.processes[j] = -1;       // sets process pids to 0 since none are running at the start
        }
        semaphore_array[i].sem.process_count = 0;
    }
}

uint64_t locate_sem(char *sem_name){
    for(int i = 0; i < MAX_SEMAPHORES; i++){
        if(semaphore_array[i].status == OCCUPIED && strCompare(semaphore_array[i].sem.name, sem_name) == 0){
            return i;
        }
    }
    return -1;
}