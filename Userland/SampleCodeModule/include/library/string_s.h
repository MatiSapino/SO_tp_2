#ifndef _STRING_S_H_
#define _STRING_S_H_

#include <stddef.h>

char *strchr(const char *str, int c);
char *strcpy(char *dest, const char *src);
int strcmp(const char *str1, const char *str2);
size_t strlen(const char *str);

void reverse(char str[], int length);

#endif