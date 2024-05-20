#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H
#include <stdint.h>
#include <stddef.h>

#define MEMORY_MANAGER_SIZE 1024

char * memory_manager(char * buffer);
void init_mm();
uint16_t get_mem(uint8_t *address, uint8_t *buffer, uint16_t count);
void get_mem_state(int mem_state[]);
void *malloc(size_t size);
void free(void *ptr);

#endif /* MEMORY_MANAGER_H */