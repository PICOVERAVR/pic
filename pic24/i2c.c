#include "i2c.h"

//hand-written i2c module because the auto-generated one is crap
//this driver does not handle multi-cycle transfers or multi-master setups

//initialize i2c module with one of three speeds: I2C_100K, I2C_400K, I2C_1M
void i2c_init(int speed) {
    ODCBbits.ODCB8 = 1; //set open-drain mode
    ODCBbits.ODCB9 = 1;
    
    ANSELBbits.ANSB8 = 0; //clear analog functions
    //no analog functionality on B9
    
    TRISBbits.TRISB8 = 0; //set as outputs
    TRISBbits.TRISB9 = 0;
    I2C1BRG = speed; //set speed to one of three values
    //WARNING: THIS ONLY WORKS AT 32Mhz, change if changing clock or add logic!
    IEC1bits.MI2C1IE = 0; 
    
    LATBbits.LATB8 = 1; //drive as 1
    LATBbits.LATB9 = 1;
    
    I2C1CONbits.I2CEN = 1;
}

void i2c_start(void) {
    I2C1CONbits.SEN = 1; //set start bit
    while (I2C1CONbits.SEN == 1); //wait until done transmitting
}

void i2c_stop(void) {
    I2C1CONbits.PEN = 1; //set stop bit
    while(I2C1CONbits.PEN == 1); //wait until done transmitting
}

bool i2c_send(uint8_t addr) {
    I2C1TRN = addr;
    while(I2C1STATbits.TBF == 1); //wait until done transmitting
    for (int i = 0; i < I2C_TIMEOUT; i++); //possible response period
    return I2C1STATbits.ACKSTAT; // 1 for NACK, 0 for ACK
}

//assumes read address has been sent
int i2c_recv(bool ackState) { // this falls apart for more than single cycle transfers
    I2C1CONbits.ACKDT = ackState; //set master to ack or nack slave transmission
    I2C1CONbits.RCEN = 1; //enable receiving, gets cleared by hardware
    while(I2C1CONbits.RCEN == 1);
    I2C1CONbits.ACKEN = 1;
    while(I2C1CONbits.ACKEN == 1);
    return I2C1RCV;
}