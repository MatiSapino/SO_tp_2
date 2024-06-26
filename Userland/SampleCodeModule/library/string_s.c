// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <string_s.h>

char *strchr(char *str, int character) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == character) {
            return str + i;
        }
    }
    return NULL;
}

char *strcpy(char *dest, const char *src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

int strcmp(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

void swap(char *c1, char *c2) {
    char aux = *c1;
    *c1 = *c2;
    *c2 = aux;
}

void reverse(char str[], int length) {
    int start = 0;
    int end = length - 1;
    while (start < end) {
        swap(str + start, str + end);
        start++;
        end--;
    }
}

size_t strlen(const char *str) {
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    return i;
}