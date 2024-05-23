#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <registers.h>

void exceptionDispatcher(int exception, registerStructT * registers);

 void zero_division();
 void invalid_opcode();
#endif