#include "header.h"
#pragma once

#define PSIZE 2

typedef struct prc {
    char *name;
    int pid;
    void (*fp)(struct prc*);
    int priority;
    
} prc;

prc mkprocess(char *name, void (*fp)(prc*), int priority);
prc *tp;