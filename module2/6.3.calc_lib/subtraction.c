#include <stdarg.h>

double operation(int argument, ...) { // вычитание
    va_list factor;
    va_start(factor, argument);
    double result = va_arg(factor, double);

    for(int i = 1; i < argument; i++) {
        result -= va_arg(factor, double);
    }
    va_end(factor);

    return result;
}

char* get_name() {
    return "Вычитание";
}
