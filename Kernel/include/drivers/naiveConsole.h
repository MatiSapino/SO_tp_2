#ifndef NAIVE_CONSOLE_H
#define NAIVE_CONSOLE_H

#include <stdint.h>
#include <lib.h>

#define deafultcolor 0x0f
#define defaultback 0x00

int get_hours();
int get_minutes();
int get_seconds();
int get_weekDay();
int get_monthDay();
int get_month();
int get_year();

void ncPrint(const char *string);
void ncPrintChar(char character);
void ncPrintCharColor(char character, char color, char back);
void ncNewline();
void ncPrintDec(uint64_t value);                 // Imprime un numero en base 10
void ncPrintHex(uint64_t value);                 // Imprime un numero en base 16
void ncPrintBin(uint64_t value);                 // Imprime un numero en base 2
void ncPrintBase(uint64_t value, uint32_t base); // Imprime un numero en la base que se le pase
void ncClear();                                  // Limpia la pantalla
void ncBackspace();                              // Borra el ultimo caracter
char *TimeClock(char *buffer);                               // Devuelve la hora actual

#endif                                           /* NAIVE_CONSOLE_H */