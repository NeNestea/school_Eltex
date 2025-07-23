#include "phonebook.h"

void add_contact_direct(phone_book **contact, int *count, int *capacity,
                        const char *first_name, const char *last_name,
                        const char *phone_number, const char *tg_link) {
  if (*count >= *capacity) {
    if (*capacity == 0) {
      *capacity = 1;
    } else {
      *capacity *= 2;
    }

    *contact = (phone_book *)realloc(*contact, *capacity * sizeof(phone_book));
    if (*contact == NULL) {
      printf("Ошибка выделения памяти\n");
      exit(1);
    }
  }

  phone_book new_contact;
  strncpy(new_contact.first_name, first_name, MAX_LEN);
  new_contact.first_name[MAX_LEN - 1] = '\0';

  strncpy(new_contact.last_name, last_name, MAX_LEN);
  new_contact.last_name[MAX_LEN - 1] = '\0';

  strncpy(new_contact.phone_number, phone_number, MAX_LEN);
  new_contact.phone_number[MAX_LEN - 1] = '\0';

  strncpy(new_contact.tg_link, tg_link, MAX_LEN);
  new_contact.tg_link[MAX_LEN - 1] = '\0';

  (*contact)[(*count)++] = new_contact;
}

void add_contact(phone_book **contact, int *count,
                 int *capacity) { // функция добавления контакта с вводом
  if (*count >= *capacity) {
    if (*capacity == 0) { // первое выделение памяти
      *capacity = 1;
    } else {
      *capacity *= 2;
    }

    *contact = (phone_book *)realloc(*contact, *capacity * sizeof(phone_book));

    if (*contact == NULL) {
      printf("Ошибка выделения памяти\n");
      exit(1);
    }
  }

  // добавляем новый контакт
  phone_book new_contact;

  printf("Введите имя: ");
  scanf("%39s", new_contact.first_name);
  printf("Введите фамилию: ");
  scanf("%39s", new_contact.last_name);
  printf("Введите номер телефона: ");
  scanf("%39s", new_contact.phone_number);
  printf("Введите ник в Telegram, если есть: ");
  scanf("%39s", new_contact.tg_link);

  (*contact)[(*count)++] = new_contact;
}

void edit_contact(phone_book *contact, int count,
                  int index) { // редактирование контакта
  if (index >= count || index < 0) {
    printf("Неверный индекс!\n\n");
    return;
  }

  phone_book *edit = &contact[index];
  printf("\n\tТекущий контакт\t\n");
  printf("1. Имя: %s\n", edit->first_name);
  printf("2. Фамилия: %s\n", edit->last_name);
  printf("3. Номер телефона: %s\n", edit->phone_number);
  printf("4. Telegram: %s\n", edit->tg_link);

  int choice;
  printf("Что вы хотите изменить? (0 - отмена): ");
  scanf("%d", &choice);

  if (choice == 0) {
    printf("Выход из режима редактирования.\n\n");
    return;
  }

  switch (choice) {
  case 1:
    printf("Введите новое имя: ");
    scanf("%39s", edit->first_name);
    break;
  case 2:
    printf("Введите новую фамилию: ");
    scanf("%39s", edit->last_name);
    break;
  case 3:
    printf("Введите номер телефона: ");
    scanf("%39s", edit->phone_number);
    break;
  case 4:
    printf("Введите Telegram: ");
    scanf("%39s", edit->tg_link);
    break;
  }

  printf("\nКонтакт успешно обновлён!\n\n");
}

void delete_contact(phone_book **contact, int *count, int *capacity,
                    int index) { // удаляем контакт
  if (index >= *count || index < 0) {
    printf("Неверный индекс!\n\n");
    return;
  }

  for (int i = index; i < *count - 1; i++) {
    (*contact)[i] = (*contact)[i + 1];
  }
  (*count)--;

  if (*count < (*capacity / 2) && *capacity > 1) {
    *capacity /= 2;
    *contact = (phone_book *)realloc(*contact, *capacity * sizeof(phone_book));
  }

  printf("Контакт успешно удалён!\n");
}

void print_contact(phone_book *contact, int count) { // вывод контактов
  if (count == 0) {
    printf("Контактов нет!\n\n");
    return;
  }


  printf("\n\tСписок контактов:\t\n");
  for (int i = 0; i < count; i++) {
    printf("%d. %s %s\n", i + 1, contact[i].first_name, contact[i].last_name);
    printf("Номер телефона: %s\n", contact[i].phone_number);
    printf("Telegram: %s\n", contact[i].tg_link);
  }
  printf("\n");
}

void menu() { // функция вывода меню
  printf("\tТелефонная книга\t\n");
  printf("1. Список контактов\n");
  printf("2. Добавить новый контакт\n");
  printf("3. Редактировать контакт\n");
  printf("4. Удалить контакт\n");
  printf("0. Выйти из телефонной книги\n");
  printf("\nВыбери пунктик: ");
}
