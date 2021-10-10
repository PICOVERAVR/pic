#include "header.h"
#pragma once

#define SD_TIMEOUT 100 //should be long enough?
#define SD_ERROR 0xFF //impossible command
#define SD_INIT_FAIL 0xFE //keep this unsigned so that uint8_t and int treat this as the same number

typedef struct sd_command { //basic SD command structure
    uint8_t command; //command with the form of 0b01xxxxxx
    uint8_t args[4]; //four arguments, all required
    uint8_t crc; //crc, usually not checked unless a CMD0 is issued
} sd_command;

typedef struct sd_resp { //40-bit response for some commands
    uint8_t resp[5];
} sd_resp;

typedef union sd_block_addr {
    uint32_t uint;
    uint8_t byte[4];
} sd_block_addr;

typedef struct sd_block { //block size is almost universally 512 bytes
    uint8_t data[512];
} sd_block;

uint8_t sd_writeCommand(sd_command *c);
sd_resp sd_writeCommandLong(sd_command *c);
void sd_readBlock(sd_block_addr block_addr, sd_block *block);
uint8_t sd_init(void);
void sd_printBlock(sd_block *block);