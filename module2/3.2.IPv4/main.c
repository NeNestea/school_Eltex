#include "IPv4.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Используйте: ./program <IP-адрес шлюза> <маска подсети> <кол-во пакетов N>\n");
        return 1;
    }

    IPv4 ip_address = parse_ip(argv[1]);
    IPv4 mask_address = parse_mask(argv[2]);

    char *endptr;
    errno = 0;
    long val = strtol(argv[3], &endptr, 10);
    if (*endptr != '\0' || errno != 0 || val <= 0) {
        printf("Ошибка: недопустимое кол-во пакетов!");
        return 1;
    }
    int N = (int)val;

    srand(time(NULL)); // для генерации случайных чисел

    int our_package = 0, other_package = 0;
    for (int i = 0; i < N; i++) {
        IPv4 ip_random = generate_random_ip();

        if (check_subnet(ip_address, ip_random, mask_address)) {
            our_package++;
        } else {
            other_package++;
        }
    }
    
    printf("Пакеты своей подсети: %d (%.2lf%%)\n", our_package, (our_package * 100.00) / N);
    printf("Пакеты другой сети: %d (%.2lf%%)\n", other_package, (other_package * 100.0) / N);

    return 0;
}
