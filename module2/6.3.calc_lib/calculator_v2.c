#include "calculator_v2.h"
#include <dirent.h>
#include <dlfcn.h>
#include <string.h>

#define LIB_DIR "./lib/"

Command commands[10]; // Максимум 10 операций
int num_commands = 0;

void menu() {
    printf("Доступные операции:\n");
    for (int i = 0; i < num_commands; i++) {
        printf("%d. %s\n", i + 1, commands[i].name);
    }
    printf("0. Выход из калькулятора\n");
    printf("\nВыберите вариант: ");
}

// Функция для загрузки библиотек
void load_libraries() {
    DIR *dir = opendir(LIB_DIR);
    if (!dir) {
        perror("Ошибка при открытии каталога библиотек");
        exit(1);
    }

    struct dirent *entry;
    while ((entry = readdir(dir))) {
        if (strstr(entry->d_name, ".so")) {
            char path[512];
            snprintf(path, sizeof(path), "%s%s", LIB_DIR, entry->d_name);
            
            void *handle = dlopen(path, RTLD_LAZY);
            if (!handle) {
                fprintf(stderr, "Ошибка загрузки %s: %s\n", path, dlerror());
                continue;
            }

            char *(*get_name)();
            double (*func)(int, ...);

            get_name = dlsym(handle, "get_name");
            func = dlsym(handle, "operation");

            if (!get_name || !func) {
                fprintf(stderr, "Ошибка: неверная библиотека %s\n", path);
                dlclose(handle);
                continue;
            }

            commands[num_commands].name = get_name();
            commands[num_commands].func = func;
            num_commands++;
        }
    }

    closedir(dir);
}
