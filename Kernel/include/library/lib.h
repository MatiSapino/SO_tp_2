#ifndef LIB_H
#define LIB_H

#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>
#include <syscalls.h>
#include <time.h>
#include <interrupts.h>

void *memset(void *destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);
void sleep(uint32_t seconds);
void sleepms(int mseconds);
void nanoms(int nseconds);
char * cpuVendor(char* vendor);
uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base); //Convierte un numero a la base que se le pase

void outb(uint16_t port, uint8_t value);
void outw(uint16_t port, uint16_t value);
uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);

char *itoa(int num, char *str, int base);

size_t strlen(const char *str);
char *strcat(char *destination, const char *source);
int strcmp(const char *str1, const char *str2);
char *strcpy(char *dest, const char *src);

#endif /* LIB_H */