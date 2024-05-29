#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <stdint.h>
#include <stddef.h>

#define MEMORY_MANAGER_SIZE 1024
#define SIZE (1024 * 1024 * 64) // 64MB
#define BASE_ADDR 0x900000
#define ADDRESS_LIMIT 0xFFFFFFFF
#define ALIGNMENT 8
#define GET_SIZE(header) (header->size & ~0x1)
#define ALIGN(size) (((size) + ALIGNMENT - 1) & ~ALIGNMENT)

void init_mm();
uint16_t get_mem(uint8_t *address, uint8_t *buffer, uint16_t count);
void get_mem_state(int mem_state[]);
void *mem_alloc(size_t size);
void free(void *ptr);

#endif /* MEMORY_MANAGER_H */