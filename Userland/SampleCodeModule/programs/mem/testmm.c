// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <mem.h>
#include <std_io.h>
#include <std_lib.h>
#include <string_s.h>
#include <testmm.h>
#include <testUtil.h>
#include <help.h> 

#define MAX_BLOCKS 128

typedef struct MM_rq {
    void *address;
    uint32_t size;
} mm_rq;

int testmm(int argc, char *argv[]) {
    int flag = 0;
    mm_rq mm_rqs[MAX_BLOCKS];
    uint8_t rq;
    uint32_t total;
    uint64_t max_memory;

    if (argc != 2){
        own_printf("argument amount is incorrect\n");
        flag++;
    } else if ((max_memory = satoi(argv[1])) <= 0) {
        own_printf("memory amount is not valid - memory amount must be a positive number\n\n");
        flag++;
    }

    if (flag > 0){
        help_testmm();
        return -1;
    }

    rq = 0;
    total = 0;

    // Request as many blocks as we can
    while (rq < MAX_BLOCKS && total < max_memory) {
        mm_rqs[rq].size = GetUniform(max_memory - total - 1) + 1;
        mm_rqs[rq].address = call_malloc(mm_rqs[rq].size);

        own_printf("block [%d] size: %d, address: %d\n", rq,
                   (int)mm_rqs[rq].size, mm_rqs[rq].address);

        if (mm_rqs[rq].address) {
            total += mm_rqs[rq].size;
            rq++;
        }
    }

    // Set
    uint32_t i;
    for (i = 0; i < rq; i++)
        if (mm_rqs[i].address)
            memset(mm_rqs[i].address, i, mm_rqs[i].size);

    // Check
    for (i = 0; i < rq; i++) {
        if (mm_rqs[i].address) {
            if (!memcheck(mm_rqs[i].address, i, mm_rqs[i].size)) {
                own_printf("test_mm ERROR\n");
                return -1;
            }
        }
    }

    // Free
    for (i = 0; i < rq; i++)
        if (mm_rqs[i].address)
            call_free(mm_rqs[i].address);

    own_printf("testmm: memory test passed!\n");
    return 0;
}