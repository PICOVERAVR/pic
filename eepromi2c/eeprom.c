#include "eeprom.h"

void eeprom_init(void) {
    //stuff here!
}

static uint16_t eeprom_read_word_internal(void) {
    uint16_t data;
    data = i2c_recv(ACK);
    data <<= 8;
    data += i2c_recv(NACK);
    return data;
}

static void eeprom_write_word_internal(uint16_t data) {
    i2c_send((data & 0xFF00) >> 8);
    i2c_send(data & 0xFF);
}

static inline void eeprom_send_addr(uint16_t addr) {
    i2c_send(addr >> 8);
    i2c_send(addr & 0xFF); //send high and low bytes
}

static bool eeprom_check_busy(void) { //is device responding? (if not, non-existant or busy)
    bool busy;
    i2c_start();
    busy = i2c_send(EEPROM_READ_ADDR);
    i2c_stop();
    return busy;
}

static inline void eeprom_wait(void) { //wait until device is not busy
    while(eeprom_check_busy());
}

void eeprom_write(uint16_t addr, uint8_t byte) {
    i2c_start();
    i2c_send(EEPROM_WRITE_ADDR);
    eeprom_send_addr(addr);
    i2c_send(byte);
    i2c_stop();
    eeprom_wait();
}

uint8_t eeprom_read(uint16_t addr) {
    i2c_start();
    i2c_send(EEPROM_WRITE_ADDR);
    eeprom_send_addr(addr);
    i2c_start();
    i2c_send(EEPROM_READ_ADDR);
    uint8_t x = i2c_recv(NACK);
    i2c_stop();
    return x;
}

void eeprom_write_word(uint16_t addr, uint16_t data) {
    i2c_start();
    i2c_send(EEPROM_WRITE_ADDR);
    eeprom_send_addr(addr);
    i2c_send((data & 0xFF00) >> 8);
    i2c_send(data & 0xFF);
    i2c_stop();
    eeprom_wait();
}

uint16_t eeprom_read_word(uint16_t addr) {
    uint16_t data;
    i2c_start();
    i2c_send(EEPROM_WRITE_ADDR);
    eeprom_send_addr(addr);
    i2c_start();
    i2c_send(EEPROM_READ_ADDR);
    data = i2c_recv(ACK);
    data <<= 8;
    data += i2c_recv(NACK);
    return data;
}

void eeprom_write_page(uint16_t addr, page *p) { // does not check for page alignment yet
    int i;
    i2c_start();
    i2c_send(EEPROM_WRITE_ADDR);
    eeprom_send_addr(addr);
    
    eeprom_write_word_internal(p->pageno);
    eeprom_write_word_internal(p->ptrb);
    eeprom_write_word_internal(p->ptrf);
    for (i = 0; i < 57; i++) {
        i2c_send(p->pagearr[i]);
    }
    i2c_stop();
    eeprom_wait();
}

page eeprom_read_page(uint16_t addr) {
    page p;
    int i;
    i2c_start();
    i2c_send(EEPROM_WRITE_ADDR);
    eeprom_send_addr(addr);
    i2c_start();
    i2c_send(EEPROM_READ_ADDR);
    
    p.pageno = eeprom_read_word_internal();
    p.ptrb = eeprom_read_word_internal();
    p.ptrf = eeprom_read_word_internal();
    for (i = 0; i < 57; i++) {
        p.pagearr[i] = i2c_recv(ACK);
    }
    p.pagearr[i] = i2c_recv(NACK); //nack this at end to signal transmission
    i2c_stop();
    return p;
}