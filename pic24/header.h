#include "mcc_generated_files/mcc.h"

#include <stdio.h> //for UART + device string processing
#include <string.h> //for memory processing
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <setjmp.h>
#include <stdbool.h>

#pragma once

#define UART_BUFSIZ 32
#define halt() __asm__("PWRSAV #1")
#define reset() __asm__("RESET")
#define nop() __asm__("NOP")

//helpful bit-twiddling tricks

#define set(num, pos) num |= (1 << pos)
#define clear(num, pos) num &= ~(1 << pos)
#define toggle(num, pos) num ^= (1 << pos)

#define MS_1 0x3F //works for only 32MHz clock!
#define MS_10 0x272
#define MS_100 0x186D
#define MS_500 0x7A20

void delay_poll(uint16_t);
void scanfs(char *dest, int lim);
uint16_t adc_convert(bool channel);
long map(int val, int ilow, int ihigh, int olow, int ohigh);
void spi_transfer(uint8_t send);