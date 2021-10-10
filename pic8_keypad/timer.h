#include "header.h"
#ifndef TIMER_HEADER_DEF
#define	TIMER_HEADER_DEF

#endif

inline void timer0_setup();

void timer0_start();
void timer0_stop();
void timer0_set(uint16_t);

void low_priority interrupt timer0_isr(void);