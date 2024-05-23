#ifndef _SOUND_DRIVER_H
#define _SOUND_DRIVER_H

#include <stdint.h>
#include <lib.h>

extern uint8_t inb(uint16_t in1);
extern void outb(uint16_t out1, uint8_t in1);

void beep(int freq);

#endif
