#ifndef CHMOD_H
#define CHMOD_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

void print_bits(mode_t law);
void print_symbols(mode_t law);
mode_t convert_symbols(mode_t current_mode, const char *bufer);
void menu();

#endif
