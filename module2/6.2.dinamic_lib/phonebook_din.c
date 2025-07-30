#include "phonebook_v2.h"

int list_length(Node *head) {
    int count = 0;
    while (head) {
        count++;
        head = head->head;
    }
    return count;
}

Node *get_node_by_index(Node *head, int index) {
    int i = 0;
    while (head && i < index) {
        head = head->head;
        i++;
    }
    return head;
}

void add_contact(Node **head) { // функция добавления контакта
  Node *new_node = malloc(sizeof(Node));
  if (!new_node) {
    printf("Ошибка выделения памяти\n");
    exit(1);
  }

  printf("Введите имя: ");
  scanf("%39s", new_node->data.first_name);
  printf("Введите фамилию: ");
  scanf("%39s", new_node->data.last_name);
  printf("Введите номер телефона: ");
  scanf("%39s", new_node->data.phone_number);
  printf("Введите ник в Telegram, если есть: ");
  scanf("%39s", new_node->data.tg_link);

  new_node->tail = new_node->head = NULL;

  if (*head == NULL) {
    *head = new_node;
    return;
  }

  Node *curr = *head;
  while (curr && strcmp(new_node->data.last_name, curr->data.last_name) > 0) {
    curr = curr->head;
  }

  if (curr == *head) {
    new_node->head = *head;
    (*head)->tail = new_node;
    *head = new_node;
  } else if (curr == NULL) {
    Node *tail = *head;
    while (tail->head) {
        tail = tail->head;
    }
    tail->head = new_node;
    new_node->tail = tail;
  } else {
    new_node->tail = curr->tail;
    new_node->head = curr;
    curr->tail->head = new_node;
    curr->tail = new_node;
  }
}

void edit_contact(Node **head, int index) { // редактирование контакта
  int length = list_length(*head);
  if (index < 0 || index >= length) {
    printf("Неверный индекс!\n");
    return;
  }

  Node *edit = get_node_by_index(*head, index);

  printf("\n\tТекущий контакт\t\n");
  printf("1. Имя: %s\n", edit->data.first_name);
  printf("2. Фамилия: %s\n", edit->data.last_name);
  printf("3. Номер телефона: %s\n", edit->data.phone_number);
  printf("4. Telegram: %s\n", edit->data.tg_link);

  int choice;
  printf("Что вы хотите изменить? (0 - отмена): ");
  scanf("%d", &choice);

  if (choice == 0) {
    printf("Выход из режима редактирования.\n\n");
    return;
  }

  char new_value[MAX_LEN];
  switch (choice) {
  case 1:
    printf("Введите новое имя: ");
    scanf("%39s", new_value);
    strcpy(edit->data.first_name, new_value);
    break;
  case 2:
    printf("Введите новую фамилию: ");
    scanf("%39s", new_value);
    strcpy(edit->data.first_name, new_value);

    {
        phone_book temp = edit->data;
        if (edit->tail) {
            edit->tail->head = edit->tail;
        } else {
            *head = edit->head;
        }

        if (edit->head) {
            edit->head->tail = edit->tail;
        }
        free(edit);

        Node *dummy = NULL;
        add_contact(&dummy);

        Node *new_node = malloc(sizeof(Node));
        new_node->data = temp;
        new_node->tail = new_node->head = NULL;
        add_contact(&(*head));
        
        return;
    }
    break;
  case 3:
    printf("Введите номер телефона: ");
    scanf("%39s", new_value);
    strcpy(edit->data.phone_number, new_value);
    break;
  case 4:
    printf("Введите Telegram: ");
    scanf("%39s", new_value);
    strcpy(edit->data.tg_link, new_value);
    break;
    default:
        printf("Неверный выбор!\n");
        return;
  }

  printf("\nКонтакт успешно обновлён!\n\n");
}

void delete_contact(Node **head, int index) { // удаляем контакт
  int length = list_length(*head);
  if (index < 0 ||  index >= length) {
    printf("Неверный индекс!\n");
    return;
  }

  Node *curr = get_node_by_index(*head, index);

  if (curr->tail) {
    curr->tail->head = curr->head;
  } else {
    *head = curr->head;
  }

  if (curr->head) {
    curr->head->tail = curr->tail;
  }

  free(curr);
  printf("Контакт успешно удалён!\n");
}

void print_contact(Node *head) { // вывод контактов
  if (!head) {
    printf("Контактов нет!\n\n");
    return;
  }

  int i = 1;
  Node *curr = head;
  printf("\n\tСписок конткактов:\n");
  while (curr) {
    printf("%d. %s %s\n", i++, curr->data.first_name, curr->data.last_name);
    printf("Номер телефона: %s\n", curr->data.phone_number);
    printf("Telegram: %s\n\n", curr->data.tg_link);
    curr = curr->head;
  }
}

void free_list(Node *head) {
    Node *tmp;
    while (head) {
        tmp = head;
        head = head->head;
        free(tmp);
    }
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
