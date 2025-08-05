#include <stdarg.h>
#include <stdio.h>

double operation(int argument, ...) { // деление
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

char* get_name() {
    return "Деление";
}
