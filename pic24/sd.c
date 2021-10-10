#include "sd.h"

//this has to have a valid crc
sd_command CMD0 = {.command = 0b01000000, .args[0] = 0, 0, 0, 0, .crc = 0b10010101};
//below commands shouldn't need a valid crc
sd_command CMD1 = {.command = 0b01000001, .args[0] = 0, 0, .args[2] = 0, .args[3] = 0, .crc = 0};
sd_command CMD8 = {.command = 0b01001000, .args[0] = 0, 0, 1, 0b10101010, .crc = 0b10000111};
sd_command CMD55 = {.command = 0b01110111, .args[0] = 0, 0, 0, 0, .crc = 0};
sd_command ACMD41 = {.command = 0b01101001, .args[0] = 0x40, 0, 0, 0, .crc = 0};
sd_command CMD58 = {.command = 0b01111010, .args[0] = 0, 0, 0, 0, .crc = 0};

sd_command CMD17 = {.command = 0b01010001, .args[0] = 0, 0, 0, 0, .crc = 0}; //read a single block

uint8_t sd_writeCommand(sd_command *c) {
    SS_SD_SetLow();
    //set upper two bits of com to 0x40 later, or check for this
    SPI2_Exchange8bit(c->command);
    
    for (int i = 0; i < 4; i++) {
        SPI2_Exchange8bit(c->args[i]);
    }
    
    SPI2_Exchange8bit(c->crc); //CRC of CMD0
    
    int time = 0;
    uint8_t result = 0xFF;
    do {
        result = SPI2_Exchange8bit(0xFF); //have to keep the MOSI line high, cycle dummy writes
        //until we get a response or the request times out
    } while (result > 0x80 && time++ < SD_TIMEOUT);
    
    SS_SD_SetHigh();
    return (time >= SD_TIMEOUT) ? SD_ERROR : result; //return the result code, or -1 if the operation timed out
}

sd_resp sd_writeCommandLong(sd_command *c) {
    sd_resp s;
    SS_SD_SetLow();
    //set upper two bits of com to 0x40 later, or check for this
    SPI2_Exchange8bit(c->command);
    
    for (int i = 0; i < 4; i++) {
        SPI2_Exchange8bit(c->args[i]);
    }
    
    SPI2_Exchange8bit(c->crc);
    
    int time = 0;
    uint8_t result = 0xFF;
    do {
        result = SPI2_Exchange8bit(0xFF); //have to keep the MOSI line high, cycle dummy writes 
        //until we get a response or the request times out
    } while (result > 0x80 && time++ < SD_TIMEOUT);
    
    if (time >= SD_TIMEOUT) {
        s.resp[0] = SD_ERROR;
    } else {
        s.resp[0] = result;
        for (int i = 1; i < 5; i++) {
            s.resp[i] = SPI2_Exchange8bit(0xFF);
        }
    }
    
    SS_SD_SetHigh();
    return s;
}

//read a block from the SD card
//this is hard-coded because there are only two commands to do this
void sd_readBlock(sd_block_addr block_addr, sd_block *block) {
    SS_SD_SetLow();
    
    SPI2_Exchange8bit(CMD17.command);
    for (int i = 3; i >= 0; i--) {
        SPI2_Exchange8bit(block_addr.byte[i]);
    }
    SPI2_Exchange8bit(CMD17.crc);
    
    uint8_t result = 0xFF;
    while (result >= 0x80) {
        result = SPI2_Exchange8bit(0xFF);
    }
    
    uint8_t token = 0;
    while (token != 0xFE) { //token for start of data transmission
        token = SPI2_Exchange8bit(0xFF);
    }
    
    for (int i = 0; i < 512; i++) {
        block->data[i] = SPI2_Exchange8bit(0xFF);
    }
    
    SS_SD_SetHigh();
}

//note: a recent SD card is assumed.  Old cards will not work.
uint8_t sd_init(void) {
    SPI2CON1bits.PPRE = 0b00; //set clock speed to ~125kHz
    for (int i = 0; i < 10; i++) {
        SPI2_Exchange8bit(0xFF);
    }
    
    uint8_t result = sd_writeCommand(&CMD0);
    if ((uint16_t) result == SD_ERROR) {
        return SD_INIT_FAIL;
    }
    
    delay_poll(MS_100);
    sd_resp r = sd_writeCommandLong(&CMD8);
    if ((uint16_t) r.resp[0] == SD_ERROR) {
        return SD_INIT_FAIL;
    }
    
    result = 0xFF;
    uint8_t time = 0;
    do {
        sd_writeCommand(&CMD55);
        result = sd_writeCommand(&ACMD41);
    } while (result != 0 && time++ < SD_TIMEOUT);
    if (time >= SD_TIMEOUT) {
        return SD_INIT_FAIL;
    }
    
    r = sd_writeCommandLong(&CMD58);
    if ((uint16_t) r.resp[0] == SD_ERROR) {
        return SD_INIT_FAIL;
    }
    SPI2CON1bits.PPRE = 0b11; //return clock speed to ~8MHz
    
    return 0;
}

static int getHexDigits(int num) {
    int digits = 0;
    
    if (num == 0) {
        return 1;
    } else {
        while(num != 0) {
            num /= 16;
            digits++;
        }
        return digits;
    }
}

void sd_printBlock(sd_block *block) {
    printf("          ");
    for (int i = 0; i < 32; i++) {
        if (getHexDigits(i) == 2) {
            printf("%x ", i);
        } else {
            printf("%x  ", i);
        }
    }
    printf("\n\n");
    
    for (int i = 0; i < 512; i += 32) {
        printf("0x%x", i);
        
        for (int spaces = 0; spaces < 8 - getHexDigits(i); spaces++) {
            printf(" ");
        }
        
        for (int j = 0; j < 32; j++) {
            uint8_t item = block->data[i + j];
            if (getHexDigits(item) == 2) {
                printf("%x ", item);
            } else {
                printf("0%x ", item);
            }
            
        }
        printf("\t");
        for (int j = 0; j < 32; j++) {
            uint8_t item = block->data[i + j];
            printf("%c", (isprint(item)) ? item : '.');
            
        }
        printf("\n");
    }
}