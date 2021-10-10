#include "timer.h"

inline void timer0_setup() {
    T0CONbits.TMR0ON = 0; //start with the timer off
    T0CONbits.T0CS = 0; //use internal system clock as clock source
    T0CONbits.T08BIT = 0; //configure as 16-bit timer
    
    T0CONbits.PSA = 0; //use the prescaler
    //by default, max prescale value
    //with current options (input clock is Fosc/4): max delay is ~8.35sec
    
    INTCONbits.T0IE = 1; //enable interrupts from timer1
    INTCONbits.T0IF = 0; //start with interrupts off
    INTCON2bits.T0IP = 0; //set timer1 overflow as low priority
}

void timer0_start() {
    T0CONbits.TMR0ON = 1;
}

void timer0_stop() {
    T0CONbits.TMR0ON = 0;
}

void timer0_set(uint16_t val) {
    TMR0L = val & 0xFF;
    TMR0H = val >> 8;
}

void low_priority interrupt timer0_isr(void) {
    TMR0IF = 0; //clear interrupt flag
    
}