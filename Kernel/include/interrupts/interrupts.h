#ifndef _INTERRUPS_H_
#define _INTERRUPS_H_

#include <stdint.h>

#define IRQ_01 1

extern void _irq00Handler(void);
extern void _irq01Handler(void);
extern void _irq02Handler(void);
extern void _irq03Handler(void);
extern void _irq04Handler(void);
extern void _irq05Handler(void);
extern void _exception0Handler(void);
extern void _exception6Handler(void);
extern uint8_t _syscall_master_handler(void);
extern void _cli(void);
extern void _sti(void);
extern void _hlt(void);
extern void picMasterMask(uint8_t mask);
extern void picSlaveMask(uint8_t mask);
extern void haltcpu(void);
extern void _force_timer_int(void);

#endif