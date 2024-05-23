#include <printmem.h>

int printmem(int argc, char *argv[])
{
    uint8_t buffer[PRINT_SIZE];
    char *endp;
    long address = strtol(argv[1], &endp, 16);

    if (*endp != '\0')
    {
        own_printf("Invalid argument.\n");
        return -1;
    }

    uint16_t copied = call_get_mem((uint8_t *)address, buffer, PRINT_SIZE);
    char *current_address = (char *)address;
    for (int i = 0; i < copied; i++)
    {
        if (i % 8 == 0)
        {
            own_printf("%s0x%x | ", i == 0 ? "" : "\n", current_address);
            current_address += 8;
        }
        uint8_t byte = buffer[i];
        if (byte <= 0xF)
        {
            own_printf("0%x ", byte);
        }
        else
        {
            own_printf("%x ", byte);
        }
    }
    own_printf("\n");

    return 0;
}