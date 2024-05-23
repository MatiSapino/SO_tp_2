#ifndef __COMMANDS_H__
#define __COMMANDS_H__

#include <UserSyscalls.h>
#include <utils.h>
#include <funcAsm.h>
#include <shell.h>
#include <snake.h>
#include <snake2.h>
#include <colors.h>
#include <printmem.h>
#include <printmemstate.h>
#include <testmm.h>

#define COMMAND_AMOUNT 15

void checkCommands(char *command, char *args[], int argCount); // searches for command
void commandNotFound(char * command);
void help(); // prints list of commands
void time(); // prints current time
void div0(); // divides by zero and throws an exception
void invalidOp(); // generates invalid opcode exception
void clearScreen();
void zoomIn();
void zoomOut();
void exitShell();
void play_snake();
void regState();
void snake2();
void memory_manager();
void print_mem();
void print_mem_state();
void test_mm();

#endif /*__COMMANDS_H__*/