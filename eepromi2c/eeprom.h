#include "i2c.h"
#pragma once

#define EEPROM_WRITE_ADDR 0xA0
#define EEPROM_READ_ADDR 0xA1

typedef struct page {
    uint16_t pageno;
    uint16_t ptrf;
    uint16_t ptrb;
    uint8_t pagearr[58];
} page;

void eeprom_init(void);

void eeprom_write(uint16_t addr, uint8_t byte);
uint8_t eeprom_read(uint16_t addr);

uint16_t eeprom_read_word(uint16_t addr);
void eeprom_write_word(uint16_t addr, uint16_t data);

void eeprom_write_page(uint16_t addr, page *p);
page eeprom_read_page(uint16_t addr);

/* Start Data Layout:
    [0-1] 0xFA65, ID for layout exist check
    [2-3] uint16_t, number of non-empty pages
    [4-5] uint16_t, ptr to first non-empty page
    
 * Page Layout:
    [0-1] uint16_t, page number
    [2-3] uint16_t, ptr to previous page
    [4-5] uint16_t, ptr to next page
 */