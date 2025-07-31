#include "phonebook_v2.h"

int main() {
  Node *head = NULL;
  int choice;

  do {
    menu();
    scanf("%d", &choice);

    switch (choice) {
    case 1: // вывод списка контактов
      print_contact(head);
      break;
    case 2: { // добавление нового контакта
      phone_book contact = get_contact_input();
      add_contact(&head, contact);
      break;
    }
    case 3: { // редактирование контакта
      int len = list_length(head);
      if (len == 0) {
        printf("Контактов нет!\n");
        break;
      }
      int index;

      printf("Выберите номер контакта для редактирования (1-%d): ", len);
      scanf("%d", &index);

      printf("\nВыберите поле для редактирования контакта: \n");
      printf("1. Имя\n2. Фамилия\n3. Телефон\n4. Телеграм\n0. Отмена\nВаш "
             "выбор: ");
      int field;
      scanf("%d", &field);
      if (field == 0) {
        printf("Отмена\n");
        break;
      }

      char new_value[MAX_LEN];
      printf("Введите новое значение: ");
      scanf("%39s", new_value);
      edit_contact(&head, index - 1, field, new_value);
      break;
    }
    case 4: { // удаление контакта
      int len = list_length(head);
      if (len == 0) {
        printf("Контактов нет!\n");
        break;
      }
      int index;

      printf("Выберите номер контакта для удаления (1-%d): ", len);
      scanf("%d", &index);
      delete_contact(&head, index - 1);
      break;
    }
    case 0:
      printf("Вы вышли из телефонной книги\n");
      break;
    default:
      printf("Неверный выбор!\n");
    }
  } while (choice != 0);

  free(head);
  return 0;
}
