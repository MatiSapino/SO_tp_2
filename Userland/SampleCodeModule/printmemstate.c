#include <printmemstate.h>

int printmemstate(int argc, char *argv[]) {
    int mem_state[3];
    call_get_mem_state(mem_state);
    own_printf("%15s %15s %10s\n", "TOTAL_MEM", "OCCUPIED_MEM", "FREE_MEM");

    own_printf("%15d %15d %10d %5s\n", mem_state[0], mem_state[1], mem_state[2], "bytes");
    return 0;
}