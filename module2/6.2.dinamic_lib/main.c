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
    case 2: // добавление нового контакта
      add_contact(&head);
      break;
    case 3: { // редактирование контакта
        int len = list_length(head);
      if (len == 0) {
        printf("Контактов нет!\n");
        break;
      }
      int index;

      printf("Выберите номер контакта для редактирования (1-%d): ", len);
      scanf("%d", &index);
      edit_contact(&head, index - 1);
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
