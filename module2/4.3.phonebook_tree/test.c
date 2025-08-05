#include <check.h>
#include "phonebook_tree.h"

phone_book make_contact(const char* fname, const char* lname, const char* phone, const char* tg) {
    phone_book c;
    strncpy(c.first_name, fname, MAX_LEN);
    strncpy(c.last_name, lname, MAX_LEN);
    strncpy(c.phone_number, phone, MAX_LEN);
    strncpy(c.tg_link, tg, MAX_LEN);
    return c;
}

START_TEST(test_insert_search_contact) {
    TreeNode* root = NULL;
    phone_book a = make_contact("Ivan", "Ivanov", "123", "@ivan");
    phone_book b = make_contact("Petr", "Petrov", "456", "@petr");

    root = insert_contact(root, a);
    root = insert_contact(root, b);

    TreeNode* found = search_contact(root, b);
    ck_assert_ptr_nonnull(found);
    ck_assert_str_eq(found->data.first_name, "Petr");

    free_tree(root);
}
END_TEST

START_TEST(test_delete_contact) {
    TreeNode* root = NULL;
    phone_book a = make_contact("Anna", "Smirnova", "789", "@anna");

    root = insert_contact(root, a);
    root = delete_contact(root, a);

    TreeNode* found = search_contact(root, a);
    ck_assert_ptr_null(found);

    free_tree(root);
}
END_TEST

START_TEST(test_edit_contact) {
    TreeNode* root = NULL;
    phone_book old = make_contact("Oleg", "Sidorov", "111", "@oleg");
    phone_book new = make_contact("Oleg", "Sidorov", "222", "@newoleg");

    root = insert_contact(root, old);
    root = edit_contact(root, old, new);

    TreeNode* found = search_contact(root, new);
    ck_assert_ptr_nonnull(found);
    ck_assert_str_eq(found->data.phone_number, "222");

    free_tree(root);
}
END_TEST

START_TEST(test_balance_tree) {
    TreeNode* root = NULL;
    // Создаем сильно несбалансированное дерево
    root = insert_contact(root, make_contact("1", "A", "1", "@a"));
    root = insert_contact(root, make_contact("2", "B", "2", "@b"));
    root = insert_contact(root, make_contact("3", "C", "3", "@c"));
    root = insert_contact(root, make_contact("4", "D", "4", "@d"));
    root = insert_contact(root, make_contact("5", "E", "5", "@e"));

    int before = tree_height(root);
    root = balance_tree(root);
    int after = tree_height(root);

    ck_assert_int_lt(after, before); // после балансировки дерево должно быть ниже

    free_tree(root);
}
END_TEST

Suite* phonebook_suite(void) {
    Suite* s;
    TCase* tc_core;

    s = suite_create("PhoneBookTree");

    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_insert_search_contact);
    tcase_add_test(tc_core, test_delete_contact);
    tcase_add_test(tc_core, test_edit_contact);
    tcase_add_test(tc_core, test_balance_tree);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int number_failed;
    Suite* s;
    SRunner* sr;

    s = phonebook_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? 0 : 1;
}
