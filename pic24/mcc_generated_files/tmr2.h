#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#pragma once

void TMR2_Initialize (void);

void TMR2_Tasks_32BitOperation( void );
void TMR2_Period32BitSet( uint32_t value );

uint32_t TMR2_Period32BitGet( void );

void TMR2_Counter32BitSet( uint32_t value );

uint32_t TMR2_Counter32BitGet( void );

void TMR2_Start( void );

void TMR2_Stop( void );

bool TMR2_GetElapsedThenClear(void);

int TMR2_SoftwareCounterGet(void);

void TMR2_SoftwareCounterClear(void);
