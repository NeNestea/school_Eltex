#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define INPUT 1024
#define ARGS 64
#define CMDS 64

int split_pipeline(char *input, char *commands[]) {
    int count = 0;
    char *cmd = strtok(input, "|");
    while (cmd != NULL && count < CMDS) {
        commands[count++] = cmd;
        cmd = strtok(NULL, "|");
    }
    return count;
}

int parse_command(char *cmd, char *args[], char **infile, char **outfile) {
    int argc = 0;
    *infile = NULL;
    *outfile = NULL;

    char *token = strtok(cmd, " \t");
    while (token != NULL && argc < ARGS - 1) {
        if (strcmp(token, "<") == 0) {
            token = strtok(NULL, " \t");
            *infile = token;
        } else if (strcmp(token, ">") == 0) {
            token = strtok(NULL, " \t");
            *outfile = token;
        } else {
            args[argc++] = token;
        }
        token = strtok(NULL, " \t");
    }
    args[argc] = NULL;
    return argc;
}

int main() {
    char input[INPUT];
    char *commands[CMDS];
    char *args[ARGS];
    char *infile, *outfile;

    while (1) {
        printf("Введите имя программы и аргументы ('exit' для выхода) => ");
        fflush(stdout);

        if (!fgets(input, INPUT, stdin)) break;
        input[strcspn(input, "\n")] = 0;
        if (strlen(input) == 0) continue;
        if (strcmp(input, "exit") == 0) break;

        int num_cmds = split_pipeline(input, commands);
        int pipefds[2 * (num_cmds - 1)];

        for (int i = 0; i < num_cmds - 1; i++) {
            if (pipe(pipefds + i*2) < 0) {
                perror("pipe");
                exit(1);
            }
        }

        for (int i = 0; i < num_cmds; i++) {
            parse_command(commands[i], args, &infile, &outfile);

            pid_t pid = fork();
            if (pid < 0) {
                perror("fork");
                exit(1);
            }

            if (pid == 0) {
                if (i == 0 && infile) {
                    int fd = open(infile, O_RDONLY);
                    if (fd < 0) { perror("open infile"); exit(1); }
                    dup2(fd, STDIN_FILENO);
                    close(fd);
                } else if (i > 0) {
                    dup2(pipefds[(i-1)*2], STDIN_FILENO);
                }
                if (i == num_cmds - 1 && outfile) {
                    int fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    if (fd < 0) { perror("open outfile"); exit(1); }
                    dup2(fd, STDOUT_FILENO);
                    close(fd);
                } else if (i < num_cmds - 1) {
                    dup2(pipefds[i*2 + 1], STDOUT_FILENO);
                }
                for (int j = 0; j < 2*(num_cmds - 1); j++) {
                    close(pipefds[j]);
                }

                execvp(args[0], args);
                perror("execvp");
                exit(1);
            }
        }

        for (int i = 0; i < 2*(num_cmds - 1); i++) close(pipefds[i]);

        for (int i = 0; i < num_cmds; i++) {
            int status;
            wait(&status);
        }
    }

    return 0;
}

/*
echo "hello world" | tr 'a-z' 'A-Z'
ls -l > output.txt
echo "Test message"
*/
