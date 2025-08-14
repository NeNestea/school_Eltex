#include <fcntl.h> 
#include <unistd.h> 
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define MAX_LEN 40
#define FILE_NAME "contacts.dat"

typedef struct phone_book {
  char first_name[MAX_LEN];
  char last_name[MAX_LEN];
  char phone_number[MAX_LEN];
  char tg_link[MAX_LEN];
} phone_book;

void add_contact(phone_book **contact, int *count, int *capacity) { // функция добавления контакта
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

void edit_contact(phone_book *contact, int count, int index) { // редактирование контакта
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

void delete_contact(phone_book **contact, int *count, int *capacity, int index) { // удаляем контакт
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

void load_contacts(phone_book **contact, int *count, int *capacity) {
    int fd = open(FILE_NAME, O_RDONLY);
    if (fd < 0) {
        *contact = NULL;
        *count = 0;
        *capacity = 0;
        return;
    }

    phone_book temp;
    *count = 0;
    *capacity = 1;
    *contact = (phone_book*)malloc(*capacity * sizeof(phone_book));

    while (read(fd, &temp, sizeof(phone_book)) == sizeof(phone_book)) {
        if (*count >= *capacity) {
            *capacity *= 2;
            *contact = (phone_book*)realloc(*contact, *capacity * sizeof(phone_book));
        }
        (*contact)[(*count)++] = temp;
    }

    close(fd);
}

void save_contacts(phone_book *contact, int count) {
    int fd = open(FILE_NAME, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        printf("Ошибка при открытии файла для записи\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        write(fd, &contact[i], sizeof(phone_book));
    }

    close(fd);
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

int main() {
  phone_book *contact =
      NULL;         // инициализируем указатель на динамический массив структур
  int count = 0;    // счётчик текущего количества контактов
  int capacity = 0; // вместимость массива

  load_contacts(&contact, &count, &capacity);

  int choice;

  do {
    menu();
    scanf("%d", &choice);

    switch (choice) {
    case 1: // вывод списка контактов
      print_contact(contact, count);
      break;
    case 2: // добавление нового контакта
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

  save_contacts(contact, count);
  free(contact);
  return 0;
}
