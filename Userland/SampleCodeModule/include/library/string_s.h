#ifndef _STRING_S_H_
#define _STRING_S_H_

#include <stddef.h>

char *strchr(const char *str, int c);
char *strcpy(char *dest, const char *src);
int strCompare(char *str1, char *str2);
void swap(char *c1, char *c2);
void reverse(char str[], int length);
size_t strlen(const char *str);
char *strtok(char *str, const char *delim);
void removePreviousSpaces(char *str);
void removeEndingSpaces(char *str);
void removeLeadingTrailingSpaces(char *str);
int parseCommand(char *buffer, char *args[]);

#endif