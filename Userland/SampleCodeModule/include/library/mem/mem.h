#ifndef _MEM_H_
#define _MEM_H_

#include <stddef.h>

void * call_malloc(size_t size);
void call_free(void *ptr);
void call_get_mem_state(int mem_state[]);

#endif