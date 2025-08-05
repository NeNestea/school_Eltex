#include "phonebook_tree.h"

int compare_contacts(const phone_book* a, const phone_book* b) {
    return strcmp(a->last_name, b->last_name);
}

TreeNode* create_node(phone_book contact) {
    TreeNode* node = malloc(sizeof(TreeNode));
    if (!node) 
        exit(1);
    
    node->data = contact;
    node->left = node->right = NULL;
    return node;
}

TreeNode* insert_contact(TreeNode* root, phone_book contact) {
    if (!root)
        return create_node(contact);
    
    if(compare_contacts(&contact, &root->data) < 0) 
        root->left = insert_contact(root->left, contact);
    else
        root->right = insert_contact(root->right, contact);
    return root;
}

TreeNode* min_value_node(TreeNode* node) {
    TreeNode* current = node;
    while (current && current->left)
        current = current->left;
    return current;
}

TreeNode* delete_contact(TreeNode* root, phone_book contact) {
    if (!root) 
        return NULL;

    int cmp = compare_contacts(&contact, &root->data);
    if (cmp < 0) 
        root->left = delete_contact(root->left, contact);
    else if (cmp > 0) 
        root->right = delete_contact(root->right, contact);
    else {
        if (!root->left) {
            TreeNode* tmp = root->right;
            free(root);
            return tmp;
        } else if (!root->right) {
            TreeNode* tmp = root->left;
            free(root);
            return tmp;
        }
        TreeNode* tmp = min_value_node(root->right);
        root->data = tmp->data;
        root->right = delete_contact(root->right, tmp->data);
    }
    return root;
}

TreeNode* search_contact(TreeNode* root, phone_book target) {
    if (!root)
        return NULL;
    
    int cmp = compare_contacts(&target, &root->data);
    if (cmp == 0)
        return root;

    return cmp < 0 ? search_contact(root->left, target) : search_contact(root->right, target);
}

TreeNode* edit_contact(TreeNode* root, phone_book old_contact, phone_book new_contact) {
    root = delete_contact(root, old_contact);
    root = insert_contact(root, new_contact);
    return root;
}

void print_contacts(TreeNode* root) {
    if (!root) 
        return;
    
    print_contacts(root->left);
    printf("%s %s\nНомер телефона: %s\nTelegram: %s\n", root->data.first_name, root->data.last_name, root->data.phone_number, root->data.tg_link);
    print_contacts(root->right);
}

void free_tree(TreeNode* root) {
    if (!root) 
        return;
    
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int tree_height(TreeNode* root) {
    if (!root)
        return 0;
    
    int l = tree_height(root->left);
    int r = tree_height(root->right);
    return (l > r ? l : r) + 1;
}

int count_nodes(TreeNode* root) {
    if (!root) 
        return 0;
    
    return 1 + count_nodes(root->left) + count_nodes(root->right);
}

void tree_to_array(TreeNode* root, phone_book* arr, int* index) {
    if (!root) 
        return;

    tree_to_array(root->left, arr, index);
    arr[(*index)++] = root->data;
    tree_to_array(root->right, arr, index);
}

TreeNode* array_to_balanced_tree(phone_book* arr, int start, int end) {
    if (start > end) 
        return NULL;
    
    int mid = (start + end) / 2;
    TreeNode* root = create_node(arr[mid]);
    root->left = array_to_balanced_tree(arr, start, mid - 1);
    root->right = array_to_balanced_tree(arr, mid + 1, end);
    return root;
}

TreeNode* balance_tree(TreeNode* root) {
    int n = count_nodes(root);
    if (n == 0)
        return NULL;

    phone_book* arr = malloc(n * sizeof(phone_book));
    int index = 0;
    tree_to_array(root, arr, &index);
    TreeNode* balanced = array_to_balanced_tree(arr, 0, n - 1);
    free(arr);
    return balanced;
}
