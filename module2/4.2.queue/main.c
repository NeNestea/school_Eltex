#include "queue.h"

int main() {
    PriorityQueue queue;
    initQueue(&queue);

    srand(time(NULL));

    // генерируем 10 случайных элементов
    for (int i = 0; i < 10; i++) {
        int value = rand() % 1000;
        unsigned char prio = rand() % 256;
        add_element(&queue, value, prio);
        printf("Элемент %d с приотритетом %d\n", value, prio);
    }

    // извлечение элементов
    printf("Первый элемент: %d\n", queueFirst(&queue));
    int val = queuePriority(&queue, 100);
    if (val == -1) { 
        printf("Элемент с приоритетом 100 не найден\n");
    } else { 
        printf("Элемент с приоритетом 100: %d\n", val);
    }
    printf("Элемент с приоритетом >= 128: %d\n", queueMin(&queue, 128));

    return 0;
}
