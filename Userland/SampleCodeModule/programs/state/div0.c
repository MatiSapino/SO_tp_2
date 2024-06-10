// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <div0.h>

int divzero(int argc ,  char * argv[]) {
    int a = 1;
    int b = 0;
    return a/b;
}