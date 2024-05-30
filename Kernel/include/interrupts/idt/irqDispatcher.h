#ifndef _IRQDISPATCHER_H
#define _IRQDISPATCHER_H

#include <time.h>
#include <stdint.h>
#include <defs.h>
#include <naiveConsole.h>
#include <interrupts.h>
#include <exceptions.h>
#include <registers.h>
#include <videoDriver.h>
#include <keyboard_buffer.h>
#include <lib.h>
#include <time.h>
#include <keyboard_driver.h>
#include <syscalls.h>
#include <sound_driver.h>
#include <memory_manager.h>
#include <pipe.h>
#include <dataDescriptor.h>
#include <semaphore.h>

void irqDispatcher(uint64_t irq, uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);

#endif