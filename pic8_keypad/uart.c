#include "uart.h"

void uart_setup(uint16_t val) {
    //set pins
    TRISCbits.TRISC7 = 1; //RX pin
    TRISCbits.TRISC6 = 1; //TX pin
    //no UART interrupts, not that important
    
    //baud rate bits
    //uint16_t spbaud = ((8000000u / val) / 64) - 1;
    uint16_t spbaud = 12; //val is not used, due to UART timing issues. number retrieved from datasheet
    
    SPBRGH = spbaud >> 8;
    SPBRG = spbaud & 0xFF;
    
    RCSTAbits.SPEN = 1; //enable the UART module
    
    TXSTAbits.TXEN = 1; //enable transmitter
    RCSTAbits.CREN = 1; //enable receiver
    
}

//methods to enable scanf and printf functionality

void putch(char c) {
    while(!TXSTAbits.TRMT); //wait for previous transmission to complete
    
    TXREG = c;
    while(!TXSTAbits.TRMT); //wait for current transmission to complete
    
//    for (int i = 0; i < 15; i++) {
//        asm("nop");
//    }
}

char getch(void) {
    while(!PIR1bits.RCIF);
    PIR1bits.RCIF = 0;
    return RCREG;
}

//add more string handling features!
