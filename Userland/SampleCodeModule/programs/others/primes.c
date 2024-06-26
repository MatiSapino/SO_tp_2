// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <std_io.h>

int isprime(int n);

int primes(int argc, char *argv[]) {
    int n = 1;
    int i = 0;
    while (1) {
        if (isprime(n)) {
            own_printf("prime [%d]:    %d\n", i, n);
            i++;
        }
        n++;
    }

    return 0;
}

int isprime(int n) {
    if (n == 0 || n == 1) {
        return 0;
    }
    if (n == 2) {
        return 1;
    }
    if (n % 2 == 0) {
        return 0;
    }
    for (int divisor = 3; divisor * divisor <= n; divisor += 2) {
        if (n % divisor == 0) {
            return 0;
        }
    }
    return 1;
}