#include "header.h"
#pragma once

#define I2C_TIMEOUT 100
#define ACK 0
#define NACK 1

#define I2C_100K 0x9D
#define I2C_400K 0x25
#define I2C_1M 0x0D

void i2c_init(int);

bool i2c_send(uint8_t);
int i2c_recv(bool);

void i2c_start(void);
void i2c_stop(void);