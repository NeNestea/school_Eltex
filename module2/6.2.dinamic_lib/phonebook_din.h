#ifndef PH_BOOK
#define PH_BOOK


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 40

typedef struct phone_book {
  char first_name[MAX_LEN];
  char last_name[MAX_LEN];
  char phone_number[MAX_LEN];
  char tg_link[MAX_LEN];
} phone_book;

typedef struct Node {
    phone_book data;
    struct Node *tail;
    struct Node *head;
} Node;

int list_length(Node *head);
Node *get_node_by_index(Node *head, int index);
void add_contact(Node **head);
void edit_contact(Node **head, int index);
void delete_contact(Node **head, int index);
void print_contact(Node *head);
void free_list(Node *head);
void menu();

#endif


