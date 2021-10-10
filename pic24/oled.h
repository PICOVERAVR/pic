#include "i2c.h"
#pragma once

#define OLED_WRITE_ADDR 0x78
#define OLED_WIDTH 128
#define OLED_HEIGHT 64

#define oled_displayon() oled_command(0xAF)
#define oled_displayoff() oled_command(0xAE)

#define OLED_SPI_BUS

//WARNING: to change display, many other parameters have to be changed as well!
//DO NOT just change these and expect the driver to work!

//note: credit is due to the Adafruit SSD1306 library, which is where a lot of the high-level code comes from.

typedef struct oled_pt {
    int x;
    int y;
} oled_pt_t;

void oled_command(uint8_t);
void oled_data(uint8_t);
void oled_init(void);

void oled_setpixel(uint16_t, uint16_t);
void oled_clearpixel(uint16_t, uint16_t);
void oled_togglepixel(uint16_t, uint16_t);

void oled_flush(void);
void oled_clear(void);

void oled_line(oled_pt_t, oled_pt_t);

void oled_char(char);
void oled_str(char *);
void oled_nl(void);

void oled_setcursor(unsigned char);
void oled_clearrow(int row);