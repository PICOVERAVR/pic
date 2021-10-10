#include <xc.h>
#include "tmr2.h"

void TMR2_Initialize(void) {
    //TMR3 0; 
    TMR3 = 0x0000;
    //PR3 0; 
    PR3 = 0x0000;
    //TMR2 0; 
    TMR2 = 0x0000;
    //Period = 0.4999980633 s; Frequency = 16006718 Hz; PR2 31264; 
    PR2 = 0x7A20;
    //TCKPS 1:256; T32 32 Bit; TON enabled; TSIDL disabled; TCS FOSC/2; TGATE disabled; 
    T2CON = 0x8038;

}

void TMR2_Tasks_32BitOperation(void) {
    /* Check if the Timer Interrupt/Status is set */
    if(IFS0bits.T3IF) {
        IFS0bits.T3IF = false;
    }
}

void TMR2_Period32BitSet(uint32_t value) {
    PR2 = (value & 0x0000FFFF);
    PR3 = ((value & 0xFFFF0000)>>16);
}

uint32_t TMR2_Period32BitGet(void) {
    uint32_t periodVal = 0xFFFFFFFF;

    periodVal = (((uint32_t)PR3 <<16) | PR2);

    return periodVal;

}

void TMR2_Counter32BitSet(uint32_t value) {
    /* Update the counter values */
   TMR3HLD = ((value & 0xFFFF0000)>>16);
   TMR2 = (value & 0x0000FFFF);

}

uint32_t TMR2_Counter32BitGet(void) {
    uint32_t countVal = 0xFFFFFFFF;
    uint16_t countValUpper;
    uint16_t countValLower;

    countValLower = TMR2;
    countValUpper = TMR3HLD;

    countVal = (((uint32_t)countValUpper<<16)| countValLower );

    return countVal ;

}

void TMR2_Start(void) {
    T2CONbits.TON = 1;
}

void TMR2_Stop(void) {
    T2CONbits.TON = false;
}