#ifndef _STD_LIB_H_
#define _STD_LIB_H_

#include <limits.h>
#include <stdint.h>

char *itoa(int num, char *str, int base);
char *ltoa(long num, char *str, int base);
long strtol(const char *nptr, char **endptr, int base);
void *memset(void *destination, int32_t c, uint64_t length);

#endif