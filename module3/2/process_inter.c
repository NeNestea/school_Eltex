#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define INPUT 1024
#define ARGS 32

int main() {
    char input[INPUT];
    char *args[ARGS];

    while (1) {
        printf("Введите имя программы и аргументы ('exit' для выхода) => ");
        fflush(stdout);

        if (!fgets(input, INPUT, stdin)) {
            break;
        }

        input[strcspn(input, "\n")] = 0;

        if (strlen(input) == 0) {
            continue;
        }

        if (strcmp(input, "exit") == 0) {
            break;
        }

        int arg_count = 0;
        char *token = strtok(input, " \t");
        while (token != NULL && arg_count < ARGS - 1) {
            args[arg_count++] = token;
            token = strtok(NULL, " \t");
        }
        args[arg_count] = NULL;
        
        pid_t pid = fork(); 
        if (pid < 0) {
            perror("fork error");
            continue;
        }

        if (pid == 0) { // дочерний процесс
            execvp(args[0], args);
            perror("exit error");
            exit(EXIT_FAILURE);
        } else { // родительский процесс
            int status;
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}
