#ifndef _STD_IO_H_
#define _STD_IO_H_

#include <colors.h>
#include <stdarg.h>
#include <stdint.h>

#include <UserSyscalls.h>

char getC();
void putC(char c, int color);
void putNewLine();
void putString(char *str, int color);
void putInt(int num);
void putIntColor(int num, int color);
void own_printf(const char *format, ...);
int own_scanf(char *format, ...);
int readInt(int *d);
int readString(char *s);
int readHexInt(int *d);

#endif