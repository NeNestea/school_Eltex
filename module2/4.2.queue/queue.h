#ifndef QUEUE
#define QUEUE

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// структура элемента
typedef struct Node {
    int data; // данные (нагрузка)
    unsigned char priority; // приоритет
    struct Node* next; // указатель на след элемент
} Node;

// структура очереди
typedef struct PriorityQueue {
    Node *head;
} PriorityQueue;

void initQueue(PriorityQueue *q);
void add_element(PriorityQueue *q, int data, unsigned char priority);
int queueFirst(PriorityQueue* q);
int queuePriority(PriorityQueue* q, unsigned char priority);
int queueMin(PriorityQueue* q, unsigned char minPriority);

#endif
