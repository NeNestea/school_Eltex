#include <check.h>
#include <stdlib.h>
#include "queue.h"

START_TEST(test_enqueue_and_dequeue)
{
    PriorityQueue q;
    initQueue(&q);

    add_element(&q, 100, 200); // высокий приоритет
    add_element(&q, 200, 100); // низкий приоритет

    ck_assert_int_eq(queueFirst(&q), 100);
    ck_assert_int_eq(queueFirst(&q), 200);
    ck_assert_int_eq(queueFirst(&q), -1);
}
END_TEST

START_TEST(test_dequeue_by_exact_priority)
{
    PriorityQueue q;
    initQueue(&q);

    add_element(&q, 1, 10);
    add_element(&q, 2, 20);
    add_element(&q, 3, 30);

    int val = queuePriority(&q, 20);
    ck_assert_int_eq(val, 2);

    val = queuePriority(&q, 50); // нет такого
    ck_assert_int_eq(val, -1);
}
END_TEST

START_TEST(test_dequeue_by_min_priority)
{
    PriorityQueue q;
    initQueue(&q);

    add_element(&q, 5, 50);
    add_element(&q, 6, 100);
    add_element(&q, 7, 150);

    int val = queueMin(&q, 100);
    ck_assert_int_eq(val, 6);

    val = queueMin(&q, 200); // никого нет
    ck_assert_int_eq(val, -1);
}
END_TEST

START_TEST(test_empty_queue_behavior)
{
    PriorityQueue q;
    initQueue(&q);

    ck_assert_int_eq(queueFirst(&q), -1);
    ck_assert_int_eq(queuePriority(&q, 123), -1);
    ck_assert_int_eq(queueMin(&q, 0), -1);
}
END_TEST

Suite* queue_suite(void)
{
    Suite* s;
    TCase* tc_core;

    s = suite_create("PriorityQueue");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_enqueue_and_dequeue);
    tcase_add_test(tc_core, test_dequeue_by_exact_priority);
    tcase_add_test(tc_core, test_dequeue_by_min_priority);
    tcase_add_test(tc_core, test_empty_queue_behavior);

    suite_add_tcase(s, tc_core);
    return s;
}

int main(void)
{
    int number_failed;
    Suite* s;
    SRunner* sr;

    s = queue_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);

    srunner_free(sr);
    return (number_failed == 0) ? 0 : 1;
}
