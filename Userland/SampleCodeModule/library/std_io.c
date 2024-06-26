// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <std_io.h>
#include <std_lib.h>
#include <stdarg.h>
#include <string_s.h>
#include <testUtil.h>

int getchar() {
    int buffer;
    if (call_read(STDIN, (char *)&buffer, 1) == -1)
        return -1;
    return buffer;
}

int putchar(int character) {
    call_write(STDOUT, (char *)&character, 1);
    return character;
}

int puts(const char *str) {
    size_t length = strlen(str);
    char new_str[length + 2];
    int i;
    for (i = 0; i < length; i++) {
        new_str[i] = str[i];
    }
    new_str[i++] = '\n';
    new_str[i] = '\0';
    return call_write(STDOUT, new_str, length + 1);
}

int own_printf(char *str, ...) {
    va_list vl;
    int i = 0, j = 0;
    char buff[1024] = {0}, tmp[20];
    char num_buff[5];
    va_start(vl, str);
    while (str && str[i]) {
        if (str[i] == '%') {
            i++;
            int min = 0;
            int s = 0;
            while (str[i] >= '0' && str[i] <= '9') {
                num_buff[s] = str[i];
                s++;
                i++;
            }
            num_buff[s] = '\0';
            switch (str[i]) {
                case 'c': {
                    buff[j] = (char)va_arg(vl, int);
                    j++;
                    min++;
                    break;
                }
                case 'd': {
                    itoa(va_arg(vl, int), tmp, 10);
                    strcpy(&buff[j], tmp);
                    j += strlen(tmp);
                    min = strlen(tmp);
                    break;
                }
                case 'x': {
                    ltoa(va_arg(vl, uint64_t), tmp, 16);
                    strcpy(&buff[j], tmp);
                    j += strlen(tmp);
                    min = strlen(tmp);
                    break;
                }
                case 'l': {
                    i++;
                    if (str[i] == 'd') {
                        ltoa(va_arg(vl, long), tmp, 10);
                        strcpy(&buff[j], tmp);
                        j += strlen(tmp);
                        min = strlen(tmp);
                    }
                    break;
                }
                case 's': {
                    char *src = va_arg(vl, char *);
                    strcpy(&buff[j], src);
                    j += strlen(src);
                    min = strlen(src);
                    break;
                }
            }
            while (min < satoi(num_buff)) {
                buff[j] = ' ';
                min++;
                j++;
            }
        } else {
            buff[j] = str[i];
            j++;
        }
        i++;
    }
    call_write(1, buff, j);
    va_end(vl);
    return j;
}

int own_scanf(char *str, ...) {
    va_list vl;
    int i = 0, j = 0, ret = 0;
    char buff[100] = {0}, c;
    c = '\0';
    char *out_loc;
    while (c != '\n') {
        call_read(STDIN, &c, 1);
        buff[i] = c;
        i++;
    }
    va_start(vl, str);
    i = 0;
    while (str && str[i]) {
        if (str[i] == '%') {
            i++;
            switch (str[i]) {
                case 'c': {
                    *(char *)va_arg(vl, char *) = buff[j];
                    j++;
                    ret++;
                    break;
                }
                case 'd': {
                    *(int *)va_arg(vl, int *) = strtol(&buff[j], &out_loc, 10);
                    j += out_loc - &buff[j];
                    ret++;
                    break;
                }
                case 'x': {
                    *(int *)va_arg(vl, int *) = strtol(&buff[j], &out_loc, 16);
                    j += out_loc - &buff[j];
                    ret++;
                    break;
                }
            }
        } else {
            buff[j] = str[i];
            j++;
        }
        i++;
    }
    va_end(vl);
    return ret;
}