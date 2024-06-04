#include <std_io.h>
#include <std_lib.h>

/*
 * Prints fibonacci sequence
 */

int fibonacci(int argc, char *argv[]) {
    int max = 200;

    int n1 = 0;
    int n2 = 1;

    if (argc > 1 && *argv[1] != '\0')
        max = strtol(argv[1], NULL, 10);

    // first two terms of the sequence
    own_printf("fibonacci [%d]:    %d\n", 0, n1);
    own_printf("fibonacci [%d]:    %d\n", 1, n2);

    int next = n1 + n2;
    int i = 2;
    while (i < max) {
        if (next < 0) {
            n1 = 0;
            n2 = 1;
            next = n1 + n2;
            i = 0;
        }
        own_printf("fibonacci [%d]:     %d\n", i, next);
        n1 = n2;
        n2 = next;
        next = n1 + n2;
        i++;
    }

    return 0;
}