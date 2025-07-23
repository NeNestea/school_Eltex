#include "calculator.h"

void menu() {
    printf("1. Сложение\n");
    printf("2. Вычитание\n");
    printf("3. Умножение\n");
    printf("4. Деление\n");
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

