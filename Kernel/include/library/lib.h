#ifndef LIB_H
#define LIB_H

#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>
#include <syscalls.h>

void *memset(void *destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);
char * cpuVendor(char* vendor);

void outb(uint16_t port, uint8_t value);
void outw(uint16_t port, uint16_t value);
uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);

int puts(const char *str);
int printf(char *str, ...);

char *itoa(int num, char *str, int base);

size_t strlen(const char *str);
char *strcat(char *destination, const char *source);
int strcmp(const char *str1, const char *str2);
char *strcpy(char *dest, const char *src);

#endif /* LIB_H */