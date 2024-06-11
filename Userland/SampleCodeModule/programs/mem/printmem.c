// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <printmem.h>
#include <std_io.h>
#include <std_lib.h>
#include <help.h>

#define PRINT_SIZE 32 // number of bytes

int printmem(int argc, char *argv[]) {
    uint8_t buffer[PRINT_SIZE];
    char *endp;
    long address = strtol(argv[1], &endp, 16);
    int flag = 0;

    if(argc < 2){
        own_printf("Invalid argument. Needs to specify memory position\n");
        flag++;
    }

    if(argv[1] < 0){
        own_printf("Invalid argument. Cannot have a negative memory position\n");
        flag++;
    }

    if (*endp != '\0') {
        own_printf("Invalid argument.\n");
        flag++;
    }

    if(flag != 0){
        help_printmem();
        return -1;
    }

    uint16_t copied = call_get_mem((uint8_t *)address, buffer, PRINT_SIZE);
    char *current_address = (char *)address;
    for (int i = 0; i < copied; i++) {
        if (i % 8 == 0) {
            own_printf("%s0x%x | ", i == 0 ? "" : "\n", current_address);
            current_address += 8;
        }
        uint8_t byte = buffer[i];
        if (byte <= 0xF) {
            own_printf("0%x ", byte);
        } else {
            own_printf("%x ", byte);
        }
    }
    own_printf("\n");

    return 0;
}