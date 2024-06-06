#ifndef _PMM_H
#define _PMM_H

#include <stddef.h>
#include <stdint.h>

void init_pmm();
void *kmalloc(size_t size);
void kfree(void *ptr);
void dump_mem();
void get_mem_state(int mem_state[]);

#endif