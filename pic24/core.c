#include "header.h"

//simple delay fuction not using interrupts, for debugging
void delay_poll(uint16_t period) {
    PR2 = (period & 0x0000FFFF);
    PR3 = ((period & 0xFFFF0000)>>16); // bitshift to get period into 2 registers
    
    T2CONbits.TON = 1; // start timer
    
    while(IFS0bits.T3IF == 0) { //poll until counter done
        ;
    }
    IFS0bits.T3IF = 0; //clear flag
}

//scan in a string, write to a NULL-terminated array
void scanfs(char *dest, int lim) { 
    int i;
    register char temp = NULL;
    for (i = 0; i < lim && temp != '\n'; i++) {
        temp = UART1_Read();
        dest[i] = temp;
    }
    dest[i+1] = NULL;
}

//read in an ADC value from 0-1023
//Enable the ADC1 pin in order to use this
uint16_t adc_convert(bool channel) {
    channel == 1 ? ADC1_ChannelSelectSet(ADC1_CHANNEL_AN0) : ADC1_ChannelSelectSet(ADC1_CHANNEL_AN1);
    AD1CON1bits.SAMP = 1; //start sampling
    for (int i = 0; i < 1000; i++);
    AD1CON1bits.SAMP = 0; //stop sampling
    while(!AD1CON1bits.DONE);
    return ADC1BUF0; //return result
}

//map range to another range, useful for ADC conversions
long map(int val, int ilow, int ihigh, int olow, int ohigh) {
    double slope = 1.0 * (ohigh - olow) / (ihigh - ilow);
    double output = olow + slope * (val - ilow);
    
    return (long) output;
}