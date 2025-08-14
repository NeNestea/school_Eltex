#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

FILE *file;
int counter = 1;
int sigint_count = 0;

void handle_signal(int sig) {
    if (sig == SIGINT) {
        sigint_count++;
        fprintf(file, "Recieve SIGINT (%d time(s))\n", sigint_count);
        fflush(file);
        if (sigint_count >= 3) {
            fclose(file);
            printf("SIGINT received 3 times, exeting\n");
            exit(0);
        } else if (sig == SIGQUIT) {
            fprintf(file, "Receives SIGQUIT\n");
            fflush(file);
        }
    }
}

int main() {
    file = fopen("output.txt", "w");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    signal(SIGINT, handle_signal);
    signal(SIGQUIT, handle_signal);

    while(1) {
        fprintf(file, "%d\n", counter);
        fflush(file);
        counter++;
        sleep(1);
    }

    fclose(file);
    return 0;
}

/*kill -SIGINT <PID>   # должен записать в файл и увеличить счётчик SIGINT
kill -SIGQUIT <PID>  # должен записать в файл, но не завершить
kill -SIGABRT <PID>  # завершит программу с аварийной ошибкой
kill -SIGKILL <PID>  # мгновенно завершает программу
kill -SIGTERM <PID>  # завершение программы
kill -SIGTSTP <PID>  # приостановка процесса
kill -SIGCONT <PID>  # продолжение приостановленного процесса
*/
