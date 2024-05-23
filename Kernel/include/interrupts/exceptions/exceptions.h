#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_

#include <registers.h>
#include <videoDriver.h>
#include <syscalls.h>

#define ZERO_EXCEPTION_ID 0
#define OPCODE_EXCEPTION_ID 6

void exceptionDispatcher(int exception, registerStructT *registers);

void zero_division();
void invalid_opcode();

#endif