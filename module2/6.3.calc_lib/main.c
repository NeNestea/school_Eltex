#include "calculator_v2.h"

extern void load_libraries(); // чтобы компилятор не ругался

int main() {
    printf("#### Добро пожаловать в калькулятор! ####\n\n");

    load_libraries(); // Загрузка .so функций

    int choice, argument;
    double a, b, c, d;
    double answer;

    do {
        menu();
        if (scanf("%d", &choice) != 1) {
            printf("Ошибка: введите число от 0 до %d!\n", num_commands);
            while (getchar() != '\n');
            continue;
        }

        if (choice < 0 || choice > num_commands) {
            printf("Ошибка: неверный вариант! Выберите 0-%d.\n", num_commands);
            continue;
        }

        if (choice != 0) {
            printf("Выберите количество аргументов (2-4): ");
            if (scanf("%d", &argument) != 1 || argument < 2 || argument > 4) {
                printf("Ошибка: введите число от 2 до 4!\n");
                while (getchar() != '\n');
                continue;
            }

            printf("Введите значения аргументов: ");
            switch (argument) {
                case 2:
                    if (scanf("%lf %lf", &a, &b) != 2) {
                        printf("Ошибка: введите числа!\n");
                        while (getchar() != '\n');
                        continue;
                    }
                    break;
                case 3:
                    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
                        printf("Ошибка: введите числа!\n");
                        while (getchar() != '\n');
                        continue;
                    }
                    break;
                case 4:
                    if (scanf("%lf %lf %lf %lf", &a, &b, &c, &d) != 4) {
                        printf("Ошибка: введите числа!\n");
                        while (getchar() != '\n');
                        continue;
                    }
                    break;
            }
        }

        if (choice > 0 && choice <= num_commands) {
            switch (argument) {
                case 2:
                    answer = commands[choice-1].func(argument, a, b);
                    break;
                case 3:
                    answer = commands[choice-1].func(argument, a, b, c);
                    break;
                case 4:
                    answer = commands[choice-1].func(argument, a, b, c, d);
                    break;
            }

            if (answer == answer) {
                printf("Ответ: %.5lf\n\n", answer);
            }
        }

    } while (choice != 0);

    return 0;
}
