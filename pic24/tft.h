#include "header.h"

#define TFT_WIDTH 320
#define TFT_HEIGHT 240
#pragma once

enum tft_color { TFT_COLOR_BLACK=0x0, TFT_COLOR_BLUE=0x001F, TFT_COLOR_RED=0xF800, 
                  TFT_COLOR_GREEN=0x07E0, TFT_COLOR_CYAN=0x07FF, TFT_COLOR_MAGENTA=0xF81F, 
                  TFT_COLOR_YELLOW=0xFFE0, TFT_COLOR_WHITE=0xFFFF
                };

void writeData(uint8_t x);
void writeCommand(uint8_t command);
void writeData16(uint16_t data);

void tft_init(void);
void tft_setPixel(uint16_t posX, uint16_t posY, uint16_t color);
void tft_setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);

void tft_fillScreen(uint16_t color);

void tft_line(uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY, uint16_t color);

void tft_char(uint16_t xStart, uint16_t yStart, char c);
void tft_str(uint16_t xStart, uint16_t yStart, char str[]);