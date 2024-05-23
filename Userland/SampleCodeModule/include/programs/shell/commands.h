#ifndef __COMMANDS_H__
#define __COMMANDS_H__

#include <string_s.h>
#include <std_io.h>
#include <screen.h>

#include <UserSyscalls.h>
#include <funcAsm.h>
#include <snake.h>
#include <snake2.h>
#include <colors.h>
#include <printmem.h>
#include <printmemstate.h>
#include <testmm.h>

#define COMMAND_AMOUNT 14

void checkCommands(char *command, char *args[], int argCount, int status);
void commandNotFound(char *command);
void help(char *args[], int argCount, int status)
void time(char *args[], int argCount, int status)
void div0(char *args[], int argCount, int status)
void invalidOp(char *args[], int argCount, int status)
void clearScreen(char *args[], int argCount, int status)
void zoomIn(char *args[], int argCount, int status)
void zoomOut(char *args[], int argCount, int status)
void exitShell(char *args[], int argCount, int status);
void play_snake(char *args[], int argCount, int status);
void regState(char *args[], int argCount, int status);
void snake2(char *args[], int argCount, int status);
void print_mem(char *args[], int argCount, int status);
void print_mem_state(char *args[], int argCount, int status);
void test_mm(char *args[], int argCount, int status);

#endif