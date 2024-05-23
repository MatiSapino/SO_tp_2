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

void checkCommands(char *command, char *args[], int argCount, int status); // searches for command
void commandNotFound(char *command);
void help();      // prints list of commands
void time();      // prints current time
void div0();      // divides by zero and throws an exception
void invalidOp(); // generates invalid opcode exception
void clearScreen();
void zoomIn();
void zoomOut();
void exitShell();
void play_snake();
void regState();
void snake2();
void print_mem(char *args[], int argCount);
void print_mem_state(char *args[], int argCount);
void test_mm(char *args[], int argCount);

#endif