#include "calculator_v2.h"

// Массив доступных команд
Command commands[] = {
    {"Сложение", addition},
    {"Вычитание", subtraction},
    {"Умножение", multiplication},
    {"Деление", division}
};

int num_commands = sizeof(commands) / sizeof(commands[0]);

void menu() {
    printf("Доступные операции:\n");
    for (int i = 0; i < num_commands; i++) {
        printf("%d. %s\n", i+1, commands[i].name);
    }
    printf("0. Выход из калькулятора\n");
    printf("\nВыберите вариант: ");
}

double addition(int argument, ...) { // сложение
    double result = 0.0;

    va_list factor;
    va_start(factor, argument);
    for(int i = 0; i < argument; i++) {
        result += va_arg(factor, double);
    }
    va_end(factor);

    return result;
}

double subtraction(int argument, ...) { // вычитание
    va_list factor;
    va_start(factor, argument);
    double result = va_arg(factor, double);

    for(int i = 1; i < argument; i++) {
        result -= va_arg(factor, double);
    }
    va_end(factor);

    return result;
}

double multiplication(int argument, ...) { // умножение
    va_list factor;
    va_start(factor, argument);
    double result = va_arg(factor, double);

    for(int i = 1; i < argument; i++) {
        result *= va_arg(factor, double);
    }
    va_end(factor);

    return result;
}

double division(int argument, ...) { // деление
    va_list factor;
    va_start(factor, argument);
    double result = va_arg(factor, double);

    for(int i = 1; i < argument; i++) {
        double divisor = va_arg(factor, double);
        if (divisor == 0.0) {
            printf("Ошибка: деление на ноль!\n");
            va_end(factor);
            return 0.0/0.0;
        }
        result /= divisor;
    }
    va_end(factor);

    return result;
}
