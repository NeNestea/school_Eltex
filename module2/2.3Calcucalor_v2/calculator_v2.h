#ifndef CALC_V2
#define CALC_V2

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

// Прототипы функций
double addition(int, ...);
double subtraction(int, ...);
double multiplication(int, ...);
double division(int, ...);

// Структура для хранения информации о команде
typedef struct {
    char* name;
    double (*func)(int, ...);
} Command;

// Объявление глобальных переменных
extern Command commands[];
extern int num_commands;

// Прототип функции меню
void menu();

int main();

#endif
