#ifndef CALC_V2
#define CALC_V2

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct {
    char* name;
    double (*func)(int, ...);
} Command;

extern Command commands[];
extern int num_commands;

void menu();

#endif
