#include <stdarg.h>

double operation(int argument, ...) { // сложение
    double result = 0.0;

    va_list factor;
    va_start(factor, argument);
    for(int i = 0; i < argument; i++) {
        result += va_arg(factor, double);
    }
    va_end(factor);

    return result;
}

char* get_name() {
    return "Сложение";
}
