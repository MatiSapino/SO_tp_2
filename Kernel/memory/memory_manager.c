#include <memory_manager.h>

size_t occupied_mem = 0;

typedef union header
{
    uint64_t size;
    uint8_t alloced : 1;
} __attribute__((packed)) header_t;

static header_t *start = (header_t *)BASE_ADDR;

void init_mm()
{
    header_t *current_header = start;

    current_header->size = SIZE;
    current_header->alloced = 0;

    current_header = current_header + 1 + GET_SIZE(current_header) / sizeof(header_t);
    current_header->size = 0;
    current_header->alloced = 1;
}

void *mem_alloc(size_t size)
{
    header_t *current_header = start;

    while (((uint64_t)current_header < BASE_ADDR + SIZE - sizeof(header_t)))
    {
        if (size <= GET_SIZE(current_header) && !current_header->alloced)
        {
            void *alloced_addr = current_header + 1;
            uint64_t old_size = GET_SIZE(current_header);
            uint64_t new_size = ALIGN(size);

            current_header->size = new_size;
            current_header->alloced = 1;

            if (new_size < old_size)
            {
                current_header = current_header + 1 + new_size / sizeof(header_t);
                current_header->size = old_size - new_size - sizeof(header_t);
                current_header->alloced = 0;
            }

            occupied_mem += new_size;
            return alloced_addr;
        }

        current_header = current_header + 1 + GET_SIZE(current_header) / sizeof(header_t);
    }

    return NULL;
}

void free(void *ptr)
{
    header_t *current_header = ptr - sizeof(header_t);

    current_header->alloced = 0;
    occupied_mem -= GET_SIZE(current_header);

    header_t *next_header = current_header + 1 + GET_SIZE(current_header) / sizeof(header_t);

    if (!next_header->alloced)
    {
        current_header->size += next_header->size + sizeof(header_t);
    }
}

void get_mem_state(int mm_state[])
{
    mm_state[0] = SIZE;
    mm_state[1] = occupied_mem;
    mm_state[2] = SIZE - occupied_mem;
}

uint16_t get_mem(uint8_t *address, uint8_t *buffer, uint16_t count)
{
    int i;
    for (i = 0; i < count; i++)
    {
        if ((uint64_t)address > ADDRESS_LIMIT)
        {
            return i;
        }
        buffer[i] = (*address);
        address++;
    }
    return i;
}