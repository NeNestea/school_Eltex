#include "chmod.h"

int main() {
    int choice;
    mode_t law = 0;

    while(1) {
        menu();
        scanf("%d", &choice);
        getchar(); // очистка буфера

        switch (choice) {
        case 1: {
            char bufer1[20];
            printf("Введите права доступа в буквенном или цифровом виде: ");
            fgets(bufer1, sizeof(bufer1), stdin);
            bufer1[strcspn(bufer1, "\n")] = '\0';

            if (bufer1[0] >= '0' && bufer1[0] <= '7') {
                law = strtol(bufer1, NULL, 8);
            } else {
                law = convert_symbols(0, bufer1); // ← начинаем с 0
            }

            printf("Буквенное обозначение: ");
            print_symbols(law);
            printf("\nЦифровое обозначение: %o", law);
            printf("\nБитовое обозначение: ");
            print_bits(law);
            printf("\n");
            break;
        }

        case 2: {
            char filename[256];
            printf("Введите имя файла/путь к файлу: ");
            fgets(filename, sizeof(filename), stdin);
            filename[strcspn(filename, "\n")] = '\0';

            struct stat file_stat;
            if (stat(filename, &file_stat) == -1) {
                perror("Ошибка! Не получена информация о файле\n");
                break;
            }

            law = file_stat.st_mode & 0777;

            printf("Буквенное обозначение: ");
            print_symbols(law);
            printf("\nЦифровое обозначение: %o", law);
            printf("\nБитовое обозначение: ");
            print_bits(law);
            printf("\n");
            break;
        }

        case 3: {
            if (law == 0) {
                printf("Сначала установите права доступа (используйте опцию 1 или 2)\n");
                break;
            }

            char bufer2[20];
            printf("Текущие права: %o\n", law);
            printf("Введите права доступа в буквенном или цифровом виде: ");
            fgets(bufer2, sizeof(bufer2), stdin);
            bufer2[strcspn(bufer2, "\n")] = '\0';

            if (bufer2[0] >= '0' && bufer2[0] <= '7') {
                law = strtol(bufer2, NULL, 8);
            } else {
                law = convert_symbols(law, bufer2); // ← используем текущие!
            }

            printf("Буквенное обозначение: ");
            print_symbols(law);
            printf("\nЦифровое обозначение: %o", law);
            printf("\nБитовое обозначение: ");
            print_bits(law);
            printf("\n");
            break;
        }

        case 0:
            exit(0);

        default:
            printf("Такого варианта нет\n");
        }
    }

    return 0;
}
