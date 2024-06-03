#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <stdint.h>
#include <stddef.h>

/**
 * @brief initializes the physical memory manager, the heap where all memory
 * blocks are going to be allocated and the tracking data structure.
 *
 */
void init_mm();

/**
 * @brief Allocates the requested memory and returns a pointer to it.
 *
 * @param size size of the memory block, in bytes.
 * @return uint64_t* pointer to the allocated memory, or NULL if the request
 * fails.
 */
void *malloc(size_t size);

/**
 * @brief Deallocates the memory previously allocated by a call kmalloc.
 *
 * @param ptr pointer to a memory block previously allocated with kmalloc.
 */
void free(void *ptr);

/**
 * @brief Dumps the blocks allocated in memory on the screen for debugging
 * purposes.
 *
 */
void dump_mem();

/**
 * @brief Dumps total memory, occupied memory and free memory into mem_state
 * 
 * @param mem_state dump is done to this array (minimum 3 length)
 */
void get_mem_state(int mem_state[]);

#endif /* MEMORY_MANAGER_H */