#ifndef _IRQDISPATCHER_H
#define _IRQDISPATCHER_H

#include <interrupts.h>
#include <time.h>
#include <keyboard_driver.h>

static void (*irq_handlers[])() = {timer_handler, keyboard_handler};

#endif