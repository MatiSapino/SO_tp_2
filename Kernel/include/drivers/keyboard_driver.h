
#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H

#include <keyboard_buffer.h>
#include <interrupts.h>

void keyboard_handler(); // handles keyboard interruptions
extern int getKey();     // gets the value of the pressed key

#endif /* KEYBOARD_DRIVER_H */