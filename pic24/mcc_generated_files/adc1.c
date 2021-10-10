#include <xc.h>
#include "adc1.h"

void ADC1_Initialize (void) {
    // ASAM disabled; ADDMABM disabled; ADSIDL disabled; DONE disabled; SIMSAM Sequential; FORM Absolute decimal result, unsigned, right-justified; SAMP disabled; SSRC Clearing sample bit ends sampling and starts conversion; AD12B 10-bit; ADON enabled; SSRCG disabled; 
   AD1CON1 = 0x8000;
    // CSCNA disabled; VCFG0 AVDD; VCFG1 AVSS; ALTS disabled; BUFM disabled; SMPI 1; CHPS 1 Channel; 
   AD1CON2 = 0x0000;
    // SAMC 0; ADRC FOSC/2; ADCS 1; 
   AD1CON3 = 0x0001;
    // CH0SA AN0; CH0SB AN0; CH0NB AVSS; CH0NA AVSS; 
   AD1CHS0 = 0x0000;
    // CSS25 disabled; CSS24 disabled; CSS31 disabled; CSS30 disabled; 
   AD1CSSH = 0x0000;
    // CSS2 disabled; CSS1 disabled; CSS0 disabled; CSS5 disabled; CSS4 disabled; CSS3 disabled; 
   AD1CSSL = 0x0000;
    // CH123SA disabled; CH123SB CH1=OA2/AN0,CH2=AN1,CH3=AN2; CH123NA disabled; CH123NB CH1=VREF-,CH2=VREF-,CH3=VREF-; 
   AD1CHS123 = 0x0000;
   
}

void ADC1_Tasks ( void ) {
    // clear the ADC interrupt flag
    IFS0bits.AD1IF = false;
}
