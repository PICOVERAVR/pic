#include "sd.h"
#pragma once

//store all file info here instead of malloc'ing it on the heap, idk why
typedef struct {
    char name[11];
    char permissions;
    sd_block *file_ptr;
    char line[32];
} sd_file;

typedef struct {
    char line[32];
} sd_entry;

int fat_init(void);
int fat_close(const char *);
int fat_traverse(void);
int fat_search(void);
int fat_flush(void);

