#include "phonebook.h"

int main() {
  phone_book *contact =
      NULL;         // инициализируем указатель на динамический массив структур
  int count = 0;    // счётчик текущего количества контактов
  int capacity = 0; // вместимость массива

  int choice;

  do {
    menu();
    scanf("%d", &choice);

    switch (choice) {
    case 1: // вывод списка контактов
      print_contact(contact, count);
      break;
    case 2: // добавление нового контакта (интерактивно)
      add_contact(&contact, &count, &capacity);
      break;
    case 3: // редактирование контакта
      if (count == 0) {
        printf("Контактов нет!\n");
        break;
      }
      int index_edit;

      printf("Выберите номер контакта для редактирования (1-%d): ", count);
      scanf("%d", &index_edit);
      edit_contact(contact, count, index_edit - 1);
      break;
    case 4: // удаление контакта
      if (count == 0) {
        printf("Контактов нет!\n");
        break;
      }
      int index_delete;

      printf("Выберите номер контакта для удаления (1-%d): ", count);
      scanf("%d", &index_delete);
      delete_contact(&contact, &count, &capacity, index_delete - 1);
      break;
    case 0:
      printf("Вы вышли из телефонной книги\n");
      break;
    default:
      printf("Неверный выбор!\n");
    }
  } while (choice != 0);

  free(contact);
  return 0;
}

