#ifndef IPV4
#define IPV4

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <errno.h>
#include <time.h>

typedef struct {
    uint8_t octet[4];
} IPv4;

IPv4 parse_ip(const char *ip_str);
IPv4 parse_mask(const char *mask_str);
IPv4 generate_random_ip();
bool check_subnet(IPv4 ip, IPv4 random_ip, IPv4 mask);

#endif
