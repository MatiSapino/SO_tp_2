#include <time.h>

static unsigned long ticks = 0;

void timer_reset() {
    ticks = 0;
}

void timer_handler() {
	ticks++;
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
    return ticks / 18;
}