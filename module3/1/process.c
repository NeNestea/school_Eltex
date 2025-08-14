#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int try_parse_int(const char *s, long long *out) {
    char *end;
    errno = 0;
    long long val = strtoll(s, &end, 10);
    if (end != s && *end == '\0' && errno == 0) {
        *out = val;
        return 1;
    }
    return 0;
}

int try_parse_double(const char *s, double *out) {
    char *end;
    errno = 0;
    double d = strtod(s, &end);
    if (end != s && *end == '\0' && errno == 0) {
        *out = d;
        return 1;
    }
    return 0;
}

void process_arg(const char *arg) {
    long long ival;
    double dval;

    if (try_parse_int(arg, &ival)) {
        if (ival > LLONG_MAX / 2 || ival < LLONG_MIN / 2) {
            double dbl = (double)ival * 2.0;
            printf("[pid %d] '%s' => целое: %lld (удвоение переполнит long long). "
                   "Удвоенное (как double): %g\n",
                   (int)getpid(), arg, ival, dbl);
        } else {
            long long doubled = ival * 2;
            printf("[pid %d] '%s' => целое: %lld, удвоенное: %lld\n",
                   (int)getpid(), arg, ival, doubled);
        }
    } else if (try_parse_double(arg, &dval)) {
        double doubled = dval * 2.0;
        printf("[pid %d] '%s' => вещественное: %g, удвоенное: %g\n",
               (int)getpid(), arg, dval, doubled);
    } else {
        printf("[pid %d] '%s' => строка: %s\n",
               (int)getpid(), arg, arg);
    }
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        fprintf(stderr, "Нет аргументов. Использование: %s arg1 arg2 ...\n", argv[0]);
        return 1;
    }

    int n = argc - 1;            
    int mid = n / 2;            

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 2;
    } else if (pid == 0) {
        if (mid == 0) {
            _exit(0);
        }
        for (int i = 1; i <= mid; ++i) {
            process_arg(argv[i]);
        }
        _exit(0);
    } else {
        int status;
        waitpid(pid, &status, 0);

        for (int i = mid + 1; i <= n; ++i) {
            process_arg(argv[i]);
        }
    }

    return 0;
}
