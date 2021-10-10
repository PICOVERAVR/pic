#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#pragma once

#define SPI2_DUMMY_DATA 0x0
#define SPI2_FIFO_FILL_LIMIT 0x8
#if (SPI2_FIFO_FILL_LIMIT > 8)

    #define SPI2_FIFO_FILL_LIMIT 8

#endif

typedef enum {
    SPI2_SHIFT_REGISTER_EMPTY  = 1 << 7,
    SPI2_RECEIVE_OVERFLOW = 1 << 6,
    SPI2_RECEIVE_FIFO_EMPTY = 1 << 5,
    SPI2_TRANSMIT_BUFFER_FULL = 1 << 1,
    SPI2_RECEIVE_BUFFER_FULL = 1 << 0
}SPI2_STATUS;

typedef enum {
    SPI2_DRIVER_TRANSFER_MODE_8BIT   = 0,
    SPI2_DRIVER_TRANSFER_MODE_16BIT  = 1,
    SPI2_DRIVER_TRANSFER_MODE_32BIT  = 2,
} SPI2_TRANSFER_MODE;

void SPI2_Initialize (void);
        
uint8_t SPI2_Exchange8bit( uint8_t data );

uint16_t SPI2_Exchange8bitBuffer(uint8_t *dataTransmitted, uint16_t byteCount, uint8_t *dataReceived);

SPI2_STATUS SPI2_StatusGet(void);