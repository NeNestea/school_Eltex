#include "IPv4.h"

// функция для парсинга строки в IP
IPv4 parse_ip(const char *ip_str) {
    IPv4 ip;
    int parsed = sscanf(ip_str, "%hhu.%hhu.%hhu.%hhu", &ip.octet[0], &ip.octet[1], &ip.octet[2], &ip.octet[3]);

    if (parsed != 4) {
        exit(1);
    }

    return ip;
}

// функция для парсинга строки в маске
IPv4 parse_mask(const char *mask_str) {
    IPv4 mask;
    int parsed = sscanf(mask_str, "%hhu.%hhu.%hhu.%hhu", &mask.octet[0], &mask.octet[1], &mask.octet[2], &mask.octet[3]);

    if (parsed != 4) {
        exit(1);
    }

    return mask;
}

// функция для генерации случайных чисел в каждом октете
IPv4 generate_random_ip() {
    IPv4 ip;
    for (int i = 0; i < 4; i++) {
        ip.octet[i] = rand() % 256; // рандомное число от 0 до 255
    }

    return ip;
}

// функция проверки принадлежности подсети
bool check_subnet(IPv4 ip, IPv4 random_ip, IPv4 mask) {
    for (int i = 0; i < 4; i++) {
        if ((ip.octet[i] & mask.octet[i]) != (random_ip.octet[i] & mask.octet[i])) {
            return false;
        }
    }
    return true;
}
