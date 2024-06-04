#ifndef _STD_LIB_H_
#define _STD_LIB_H_

#include <stddef.h>
#include <stdint.h>

#define EOF -1

char *itoa(int num, char *str, int base);
char *ltoa(long num, char *str, int base);
long strtol(const char *nptr, char **endptr, int base);
void *memset(void *destiny, int32_t c, uint64_t length);

#endif /* _STD_LIB_H_ */