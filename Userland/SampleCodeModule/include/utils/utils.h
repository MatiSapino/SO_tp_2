#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <UserSyscalls.h>
#include <buffer.h>
#include <colors.h>
#include <limits.h>

typedef enum pstatus {
    WAITING = 0,
    READY,
    TERMINATED,
} pstatus_t;

char getC();
void putC(char c, int color);
void putString(char * str, int color);
int strCompare(char * str1, char * str2);
void clearScreen();
void removeLeadingTrailingSpaces(char* str);
void removePreviousSpaces(char* str);
void removeEndingSpaces(char* str);
void putNewLine();
void putInt(int num);
void putIntColor(int num, int color);
void putCursor();
void removeCursor();
void own_printf(const char * format, ...);
int own_scanf(char * format, ...);
int readInt(int* d);
int readString(char *s);
int readHexInt(int* d);
void setFontSize(int size);
void putCharColorPos(char character, int color, int x, int y);
void putSquare(int x, int y, int size, int color);
long strtol(const char *nptr, char **endptr, int base);
int isspace(int c);
int isdigit(int c);
int isalpha(int c);
int islower(int c);
int isupper(int c);
int64_t satoi(char *str);
uint32_t GetUint();
uint32_t GetUniform(uint32_t max);
void *memset(void *destination, int32_t c, uint64_t length);
uint8_t memcheck(void *start, uint8_t value, uint32_t size);
char *itoa(int num, char *str, int base);
char *strcpy(char *dest, const char *src);
size_t strlen(const char *str);
char *ltoa(long num, char *str, int base);
void reverse(char str[], int length);
void swap(char *c1, char *c2);
char* strtok(char* str, const char* delim);
char* strchr(const char* str, int c);
void endless_loop();
#endif /* UTILS_H */