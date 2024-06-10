// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <std_io.h>
#include <std_lib.h>

/*
 * Prints fibonacci sequence
 */

int fibonacci(int argc, char *argv[]) {

    int max = 500;

    if (argc > 1 && *argv[1] != '\0')
        max = strtol(argv[1], NULL, 10);


    long n1 = 0;
    long n2 = 1;

    // first two terms of the sequence
    own_printf("fibonacci [%d]:    %d\n", 0, n1);
    own_printf("fibonacci [%d]:    %d\n", 1, n2);

    long next = n1 + n2;
    int i = 2;
    while (i < max && next > 0) {
        own_printf("fibonacci [%d]:     %ld\n", i, next);
        n1 = n2;
        n2 = next;
        next = n1 + n2;
        i++;
    }

    return 0;
}