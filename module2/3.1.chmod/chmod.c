#include "chmod.h"

void print_bits(mode_t law) {
    for (int i = 8; i >= 0; i--) {
        printf("%d", (law & (1 << i)) ? 1 : 0);
        if (i % 3 == 0) {
            printf(" ");
        }
    }
}

void print_symbols(mode_t law) {
    char symbol[10];
    symbol[0] = (law & S_IRUSR) ? 'r' : '-';
    symbol[1] = (law & S_IWUSR) ? 'w' : '-';
    symbol[2] = (law & S_IXUSR) ? 'x' : '-';
    symbol[3] = (law & S_IRGRP) ? 'r' : '-';
    symbol[4] = (law & S_IWGRP) ? 'w' : '-';
    symbol[5] = (law & S_IXGRP) ? 'x' : '-';
    symbol[6] = (law & S_IROTH) ? 'r' : '-';
    symbol[7] = (law & S_IWOTH) ? 'w' : '-';
    symbol[8] = (law & S_IXOTH) ? 'x' : '-';
    symbol[9] = '\0';

    printf("%s", symbol);
}

mode_t convert_symbols(mode_t current_mode, const char *bufer) {
    mode_t mode = current_mode;
    const char *from_bufer = bufer;

    while (*from_bufer) {
        mode_t who = 0;
        mode_t right = 0;

        // u/g/o/a
        while (*from_bufer && (*from_bufer != '+' && *from_bufer != '-' && *from_bufer != '=')) {
            switch (*from_bufer) {
                case 'u': who |= S_IRWXU; break;
                case 'g': who |= S_IRWXG; break;
                case 'o': who |= S_IRWXO; break;
                case 'a': who |= S_IRWXU | S_IRWXG | S_IRWXO; break;
                default:
                    fprintf(stderr, "Был введён неверный символ\n");
                    exit(1);
            }
            from_bufer++;
        }

        if (!*from_bufer) break;
        char sign = *from_bufer++;

        // r/w/x
        while (*from_bufer && *from_bufer != ',' && *from_bufer != ';') {
            switch (*from_bufer) {
                case 'r': right |= S_IRUSR | S_IRGRP | S_IROTH; break;
                case 'w': right |= S_IWUSR | S_IWGRP | S_IWOTH; break;
                case 'x': right |= S_IXUSR | S_IXGRP | S_IXOTH; break;
                default:
                    fprintf(stderr, "Был введён неверный символ\n");
                    exit(1);
            }
            from_bufer++;
        }

        switch (sign) {
            case '+':
                mode |= (who & right);
                break;
            case '-':
                mode &= ~(who & right);
                break;
            case '=':
                mode = (mode & ~who) | (right & who);
                break;
            default:
                fprintf(stderr, "Неверный знак\n");
                exit(1);
        }

        if (*from_bufer == ',' || *from_bufer == ';') {
            from_bufer++;
        }
    }

    return mode;
}

void menu() {
    printf("\nМеню:\n");
    printf("1. Ввести права доступа\n");
    printf("2. Ввести имя файла для предоставления прав доступа\n");
    printf("3. Изменить права доступа\n");
    printf("0. Выход\n");
    printf("Выберите вариант: ");
}
