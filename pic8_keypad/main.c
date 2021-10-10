#include "header.h"
#include "setup.h"
#include "uart.h"

//const enum buttons {KEY_ENTER, KEY_ENTER2, KEY_NO, KEY_YES, KEY_WAGON, KEY_SOUND, KEY_DOWN, KEY_RIGHT, KEY_LEFT, KEY_UP}; //figure out all key positions

int kpd_read() {
    uint8_t temp = PORTA;
    uint8_t tempc = PORTC;
    temp ^= 1UL << 1; //had to do some bit level hacking in software to correct pullups
    temp ^= 1UL << 2;
    temp ^= 1UL << 3;
    temp ^= 1UL << 5;
    temp ^= 1UL << 6;
    
    tempc = tempc & 0b11; //cut off the high portc values
    tempc ^= 1UL << 1;
    tempc ^= 1UL << 0;
    
    return temp | ((tempc & 3) << 8);
}
//kpd pins used: RA0 - RA6
//               RC0 - RC1

void main(void) {
    system_setup();
    uart_setup(9600);

    char buffer[10];
    TRISBbits.TRISB0 = 0;
    
    asm("nop");
    
    asm("nop");
    for(;;) {
        
        PORTBbits.RB0 = ~PORTBbits.RB0;
//        uint16_t temp = kpd_read();
//        
//        putchar(':');
//        
//        itoa(buffer, kpd_read(), 10);
//        
//        for (unsigned int i = 0; buffer[i] != '\0'; i++) {
//            putchar(buffer[i]);
//        }
//        
//        putchar('\n');
        
        
//        printf(":%d\n", kpd_read());
//        for (int i = 0; i < 1500; i++) {
//            asm("nop");
//        }
//        
    }
}