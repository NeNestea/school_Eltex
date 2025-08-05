#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

// инициализация очереди
void initQueue(PriorityQueue *q) {
    q->head = NULL;
}

// добавление элемента
void add_element(PriorityQueue *q, int data, unsigned char priority) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->priority = priority;
    new_node->next = NULL;

    // очередь пуста или приоритет выше головы — вставляем в начало
    if (q->head == NULL || priority > q->head->priority) {
        new_node->next = q->head;
        q->head = new_node;
        return;
    }

    // ищем место для вставки
    Node* current = q->head;
    while (current->next != NULL && current->next->priority >= priority) {
        current = current->next;
    }

    new_node->next = current->next;
    current->next = new_node;
}

// извлечение первого элемента
int queueFirst(PriorityQueue* q) {
    if (q->head == NULL) {
        printf("Очередь пустая\n");
        return -1;
    }

    Node* temp = q->head;
    int data = temp->data;
    q->head = temp->next;
    free(temp);
    return data;
}

// извлечение по точному приоритету
int queuePriority(PriorityQueue* q, unsigned char priority) {
    if (q->head == NULL) {
        printf("Очередь пуста!\n");
        return -1;
    }

    Node* current = q->head;
    Node* prev = NULL;

    while (current != NULL && current->priority >= priority) {
        if (current->priority == priority) {
            int data = current->data;
            if (prev == NULL)
                q->head = current->next;
            else
                prev->next = current->next;
            free(current);
            return data;
        }
        prev = current;
        current = current->next;
    }

    return -1;
}

int queueMin(PriorityQueue* q, unsigned char minPriority) {
    if (q->head == NULL) {
        printf("Очередь пуста!\n");
        return -1;
    }

    Node* current = q->head;
    Node* prev = NULL;
    Node* target = NULL;
    Node* target_prev = NULL;

    while (current != NULL) {
        if (current->priority >= minPriority) {
            target = current;
            target_prev = prev;
        }
        prev = current;
        current = current->next;
    }

    if (target != NULL) {
        int data = target->data;
        if (target_prev == NULL)
            q->head = target->next;
        else
            target_prev->next = target->next;
        free(target);
        return data;
    }

    printf("Элемент с приоритетом >= %d не найден\n", minPriority);
    return -1;
}
