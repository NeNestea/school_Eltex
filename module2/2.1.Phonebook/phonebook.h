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


void add_contact_direct(phone_book **contact, int *count, int *capacity, const char *first_name, const char *last_name, const char *phone_number, const char *tg_link);
void add_contact(phone_book **contact, int *count, int *capacity);
void edit_contact(phone_book *contact, int count, int index);
void delete_contact(phone_book **contact, int *count, int *capacity, int index);
void print_contact(phone_book *contact, int count);
void menu();

int main();

#endif 
