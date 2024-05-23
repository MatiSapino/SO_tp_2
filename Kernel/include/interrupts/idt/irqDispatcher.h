#ifndef _IRQDISPATCHER_H
#define _IRQDISPATCHER_H

#include <stdint.h>

void irqDispatcher(uint64_t irq, uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);

#endif