#include <check.h>
#include "calculator_v2.h" // так назовём твой файл без main (вынеси функции туда отдельно)
#include <math.h>

START_TEST(test_addition)
{
    ck_assert_double_eq_tol(addition(2, 2.0, 3.0), 5.0, 1e-6);
    ck_assert_double_eq_tol(addition(3, 1.0, 2.0, 3.0), 6.0, 1e-6);
    ck_assert_double_eq_tol(addition(4, -1.0, 2.0, -3.0, 4.0), 2.0, 1e-6);
}
END_TEST

START_TEST(test_subtraction)
{
    ck_assert_double_eq_tol(subtraction(2, 5.0, 2.0), 3.0, 1e-6);
    ck_assert_double_eq_tol(subtraction(3, 10.0, 3.0, 2.0), 5.0, 1e-6);
    ck_assert_double_eq_tol(subtraction(4, 10.0, 1.0, 2.0, 3.0), 4.0, 1e-6);
}
END_TEST

START_TEST(test_multiplication)
{
    ck_assert_double_eq_tol(multiplication(2, 3.0, 4.0), 12.0, 1e-6);
    ck_assert_double_eq_tol(multiplication(3, 2.0, -2.0, 1.5), -6.0, 1e-6);
    ck_assert_double_eq_tol(multiplication(4, 1.0, 2.0, 3.0, 4.0), 24.0, 1e-6);
}
END_TEST

START_TEST(test_division)
{
    ck_assert_double_eq_tol(division(2, 8.0, 2.0), 4.0, 1e-6);
    ck_assert_double_eq_tol(division(3, 100.0, 5.0, 2.0), 10.0, 1e-6);
}
END_TEST

START_TEST(test_division_by_zero)
{
    double result = division(2, 5.0, 0.0);
    ck_assert(isnan(result));
}
END_TEST

Suite* calculator_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Calculator");

    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_addition);
    tcase_add_test(tc_core, test_subtraction);
    tcase_add_test(tc_core, test_multiplication);
    tcase_add_test(tc_core, test_division);
    tcase_add_test(tc_core, test_division_by_zero);

    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = calculator_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? 0 : 1;
}
