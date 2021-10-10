#include "timer.h"
#include "uart.h"
#include "setup.h"

inline void io_setup() {
    ADCON1bits.PCFG = 0b1111; //set all PORTA bits to digital
    TRISA = 0x7F; //set all of port A to be inputs
    TRISC = 0x03;
    
    //have to config part of port B as well
}

inline void interrupt_setup() {
    INTCONbits.GIE = 1; //enables all interrupts
    INTCONbits.PEIE = 1; //enables all peripheral interrupts   
}

inline void system_setup() {
    //osc config
    OSCCONbits.IRCF = 0b111; //8MHz clock
    OSCCONbits.SCS = 0b11; //use the internal osc
    //note: the OSC pins may need additional setup to use
    //since they are clocking the USB module
    
    //all of these peripherals need to be on by default
    io_setup();
    timer0_setup();
    
    interrupt_setup();
}