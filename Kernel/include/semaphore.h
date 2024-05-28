#ifndef SEMAPHORE_H
#define SEMAPHORE_H
#include <stdint.h>
#include <circularLinkedList.h>

#define MAX_SEMAPHORE_NAME_LENGTH 15
#define MAX_SEMAPHORES 128 
#define MAX_PROCESSES 1024
#define AVAILABLE 1
#define OCCUPIED 0


typedef struct {
    char name[MAX_SEMAPHORE_NAME_LENGTH];
    // node_list_t *head;                       // no los encuentra porque los structs no entan en linkedList.h sino en el .c
    // node_list_t *tail;
    int mutex;
    int value;
    int processes[MAX_PROCESSES];               // pids of all processes in the semaphore
    int process_count;                          // number of processes in the semaphore 
    uint8_t status;                            // 1 if available, 0 if occupied
} semaphore;



uint64_t my_sem_up(char* semaphore_name);

uint64_t my_sem_down(char* semaphore_name);

uint64_t my_sem_open(char* semaphore_name, uint64_t initial_value);

uint64_t my_sem_close(char* semaphore_name);

uint64_t locate_sem(char *sem_name);                    // returns the semaphore position in the array if found, if not returns -1

void initailize_sems();                                 // sets all semaphores to available 
#endif