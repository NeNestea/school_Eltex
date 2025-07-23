#include "calculator.h"

int main() {
    printf("####Добро пожаловать в калькулятор!####\n\n");

    int choice, argument;
    double a, b, c, d;
    double answer;
    do
    {
        menu();
        if (scanf("%d", &choice) != 1) { // Если ввод не число
            printf("Ошибка: введите число от 0 до 4!\n");
            while (getchar() != '\n');
            continue;
        }

        if (choice < 0 || choice > 4) {
            printf("Ошибка: неверный вариант! Выберите 0-4.\n");
            continue;
        }

        if (choice != 0) {
            printf("Выберите количество аргументов (2-4): ");
            if (scanf("%d", &argument) != 1 || argument < 2 || argument > 4) {
                printf("Ошибка: введите число от 2 до 4!\n");
                while (getchar() != '\n'); // Пропускаем некорректный ввод
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

        switch (choice)
        {
        case 1: // сложение
            if (argument == 2) {
                answer = addition(argument, a, b);
            } else if (argument == 3) {
                answer = addition(argument, a, b, c);
            } else if (argument == 4) {
                answer = addition(argument, a, b, c, d);
            }
            printf("Ответ: %.5lf\n\n", answer);
            break;
        case 2: // вычитание
            if (argument == 2) {
                answer = subtraction(argument, a, b);
            } else if (argument == 3) {
                answer = subtraction(argument, a, b, c);
            } else if (argument == 4) {
                answer = subtraction(argument, a, b, c, d);
            }
            printf("Ответ: %.5lf\n\n", answer);
            break;
        case 3: // умножение
            if (argument == 2) {
                answer = multiplication(argument, a, b);
            } else if (argument == 3) {
                answer = multiplication(argument, a, b, c);
            } else if (argument == 4) {
                answer = multiplication(argument, a, b, c, d);
            }
            printf("Ответ: %.5lf\n\n", answer);
            break;
        case 4: // деление
            if (argument == 2) {
                answer = division(argument, a, b);
            } else if (argument == 3) {
                answer = division(argument, a, b, c);
            } else if (argument == 4) {
                answer = division(argument, a, b, c, d);
            }

            if (answer == answer) {
                printf("Ответ: %.5lf\n\n", answer);
            }
            break;
        case 0: // выход
            break;
        
        default: printf("\nТакого варианта нет!\n");
            break;
        }
    } while (choice != 0);
    
    return 0;
}
