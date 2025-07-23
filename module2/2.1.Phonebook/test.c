#include <check.h>
#include <stdlib.h>
#include <string.h>
#include "phonebook.h"

START_TEST(test_add_contact) {
  phone_book *contacts = NULL;
  int count = 0;
  int capacity = 0;

  add_contact_direct(&contacts, &count, &capacity, "Ivan", "Ivanov", "+123456789", "ivanTG");

  ck_assert_int_eq(count, 1);
  ck_assert_str_eq(contacts[0].first_name, "Ivan");
  ck_assert_str_eq(contacts[0].last_name, "Ivanov");
  ck_assert_str_eq(contacts[0].phone_number, "+123456789");
  ck_assert_str_eq(contacts[0].tg_link, "ivanTG");

  free(contacts);
}
END_TEST

START_TEST(test_delete_contact) {
  phone_book *contacts = NULL;
  int count = 0;
  int capacity = 0;

  add_contact_direct(&contacts, &count, &capacity, "Ivan", "Ivanov", "+123456789", "ivanTG");
  add_contact_direct(&contacts, &count, &capacity, "Petr", "Petrov", "+987654321", "petrTG");

  delete_contact(&contacts, &count, &capacity, 0); // удаляем первый

  ck_assert_int_eq(count, 1);
  ck_assert_str_eq(contacts[0].first_name, "Petr");
  ck_assert_str_eq(contacts[0].last_name, "Petrov");

  free(contacts);
}
END_TEST

Suite *phone_book_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("PhoneBook");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_add_contact);
  tcase_add_test(tc_core, test_delete_contact);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = phone_book_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? 0 : 1;
}
