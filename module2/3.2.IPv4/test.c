#include <unistd.h>
#include <sys/wait.h>
#include <check.h>
#include "IPv4.h"

START_TEST(test_parse_ip_valid) {
    IPv4 ip = parse_ip("192.168.1.1");
    ck_assert_uint_eq(ip.octet[0], 192);
    ck_assert_uint_eq(ip.octet[1], 168);
    ck_assert_uint_eq(ip.octet[2], 1);
    ck_assert_uint_eq(ip.octet[3], 1);
}
END_TEST

START_TEST(test_parse_ip_invalid) {
    if (fork() == 0) {
        parse_ip("bad.ip.string"); // ожидается выход
        exit(EXIT_FAILURE);        // не должен сюда дойти
    } else {
        int status;
        wait(&status);
        ck_assert(WIFEXITED(status));
        ck_assert_int_eq(WEXITSTATUS(status), EXIT_FAILURE);
    }
}
END_TEST

START_TEST(test_parse_mask_valid) {
    IPv4 mask = parse_mask("255.255.255.0");
    ck_assert_uint_eq(mask.octet[0], 255);
    ck_assert_uint_eq(mask.octet[1], 255);
    ck_assert_uint_eq(mask.octet[2], 255);
    ck_assert_uint_eq(mask.octet[3], 0);
}
END_TEST

START_TEST(test_check_subnet_true) {
    IPv4 ip = { .octet = {192, 168, 1, 1} };
    IPv4 random_ip = { .octet = {192, 168, 1, 100} };
    IPv4 mask = { .octet = {255, 255, 255, 0} };
    ck_assert(check_subnet(ip, random_ip, mask) == true);
}
END_TEST

START_TEST(test_check_subnet_false) {
    IPv4 ip = { .octet = {192, 168, 1, 1} };
    IPv4 random_ip = { .octet = {192, 168, 2, 100} };
    IPv4 mask = { .octet = {255, 255, 255, 0} };
    ck_assert(check_subnet(ip, random_ip, mask) == false);
}
END_TEST

Suite *ip_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("IPv4");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_parse_ip_valid);
    tcase_add_test(tc_core, test_parse_ip_invalid);
    tcase_add_test(tc_core, test_parse_mask_valid);
    tcase_add_test(tc_core, test_check_subnet_true);
    tcase_add_test(tc_core, test_check_subnet_false);

    suite_add_tcase(s, tc_core);
    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = ip_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);

    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
