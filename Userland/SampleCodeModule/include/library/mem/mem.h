#ifndef _MEM_H_
#define _MEM_H_

#include <stddef.h>
#include <stdint.h>

void * call_malloc(size_t size);
void call_free(void *ptr);
int call_get_mem(uint8_t *address, uint8_t *buffer, size_t count);
void call_get_mem_state(int mem_state[]);

#endif