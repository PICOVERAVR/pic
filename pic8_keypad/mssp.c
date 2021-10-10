#include "mssp.h"


//the MSSP is hardware that acts as either a hardware SPI unit or a hardware I2C unit
int mssp_init(int mssp_mode, int speed) {
    if (mssp_mode == MSSP_I2C_SLAVE) {
        
        
        
        
        return 0;
    } else {
        return -1; //invalid option called!
    }
}