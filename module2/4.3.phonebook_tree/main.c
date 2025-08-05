#include "phonebook_tree.h"

phone_book get_contact_input() {
  phone_book contact;
  printf("Введите имя: ");
  scanf("%39s", contact.first_name);
  printf("Введите фамилию: ");
  scanf("%39s", contact.last_name);
  printf("Введите номер телефона: ");
  scanf("%39s", contact.phone_number);
  printf("Введите ник в Telegram, если есть: ");
  scanf("%39s", contact.tg_link);

  return contact;
}

void menu() { // функция вывода меню
  printf("\tТелефонная книга\t\n");
  printf("1. Список контактов\n");
  printf("2. Добавить новый контакт\n");
  printf("3. Редактировать контакт\n");
  printf("4. Удалить контакт\n");
  printf("5. Сбалансировать дерево\n");
  printf("0. Выйти из телефонной книги\n");
  printf("\nВыбери пунктик: ");
}

int main() {
  TreeNode *root = NULL;
  int choice;

  do {
    menu();
    scanf("%d", &choice);
    getchar();

    switch (choice) {
    case 1: // вывод списка контактов
      print_contacts(root);
      break;
    case 2: { // добавление нового контакта
      phone_book contact = get_contact_input();
      root = insert_contact(root, contact);
      break;
    }
    case 3: { // редактирование контакта
      printf("Введите контакт для редактирования:\n");
      phone_book old = get_contact_input();

        printf("Введите новый контакт:\n");
        phone_book new = get_contact_input();
        root = edit_contact(root, old, new);
        break;
    }
    case 4: { // удаление контакта
        printf("Введите контакт для удаления:\n");
        phone_book c = get_contact_input();
        root = delete_contact(root, c);
        break;
    }
    case 5:
        root = balance_tree(root);
        printf("Дерево сбалансировано.\n");
        break;
    case 0:
      printf("Вы вышли из телефонной книги\n");
      break;
    default:
      printf("Неверный выбор!\n");
    }
  } while (choice != 0);

  free(root);
  return 0;
}
