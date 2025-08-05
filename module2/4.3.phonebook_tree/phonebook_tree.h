#ifndef TREE
#define TREE

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

typedef struct TreeNode {
    phone_book data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

int compare_contacts(const phone_book* a, const phone_book* b);
TreeNode* create_node(phone_book contact);
TreeNode* insert_contact(TreeNode* root, phone_book contact);
TreeNode* min_value_node(TreeNode* node);
TreeNode* delete_contact(TreeNode* root, phone_book contact);
TreeNode* search_contact(TreeNode* root, phone_book target);
TreeNode* edit_contact(TreeNode* root, phone_book old_contact, phone_book new_contact);
void print_contacts(TreeNode* root);
void free_tree(TreeNode* root);

int tree_height(TreeNode* root);
int count_nodes(TreeNode* root);
void tree_to_array(TreeNode* root, phone_book* arr, int* index);
TreeNode* array_to_balanced_tree(phone_book* arr, int start, int end);
TreeNode* balance_tree(TreeNode* root);

#endif
