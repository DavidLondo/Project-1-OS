#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "queue.h"

#define INITIAL_CAPACITY 8

struct Queue {
    QueueData* data;
    int front;
    int rear;
    int size;
    int capacity;
};

Queue* queue_create() {
    Queue* q = malloc(sizeof(Queue));
    assert(q != NULL);

    q->capacity = INITIAL_CAPACITY;
    q->data = malloc(q->capacity * sizeof(QueueData));
    assert(q->data != NULL);

    q->front = 0;
    q->rear = -1;
    q->size = 0;
    return q;
}

void queue_destroy(Queue* q, bool free_data) {
    if (!q) return;
    if (free_data) {
        for (int i = 0; i < q->size; i++) {
            void* ptr = q->data[(q->front + i) % q->capacity];
            free(ptr);
        }
    }
    free(q->data);
    free(q);
}

bool queue_is_empty(const Queue* q) {
    assert(q != NULL);
    return q->size == 0;
}

bool queue_is_full(const Queue* q) {
    assert(q != NULL);
    return q->size == q->capacity;
}

void queue_enqueue(Queue* q, QueueData value) {
    assert(q != NULL);

    if (queue_is_full(q)) {
        int new_capacity = q->capacity * 2;
        QueueData* new_data = malloc(new_capacity * sizeof(QueueData));
        assert(new_data != NULL);

        // Copiar datos en orden correcto
        for (int i = 0; i < q->size; ++i) {
            new_data[i] = q->data[(q->front + i) % q->capacity];
        }

        free(q->data);
        q->data = new_data;
        q->capacity = new_capacity;
        q->front = 0;
        q->rear = q->size - 1;
    }

    q->rear = (q->rear + 1) % q->capacity;
    q->data[q->rear] = value;
    q->size++;
}

QueueData queue_dequeue(Queue* q) {
    assert(q != NULL);

    if (queue_is_empty(q)) {
        fprintf(stderr, "Queue underflow: intentando dequeue en cola vacía\n");
        exit(EXIT_FAILURE);
    }

    QueueData value = q->data[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return value;
}

QueueData queue_peek(const Queue* q) {
    assert(q != NULL);
    if (queue_is_empty(q)) return NULL;
    return q->data[q->front];
}

void queue_debug_print(const Queue* q) {
    assert(q != NULL);
    printf("Queue Debug: size=%d, capacity=%d, front=%d, rear=%d\n",
           q->size, q->capacity, q->front, q->rear);
    for (int i = 0; i < q->size; i++) {
        printf("  [%d] = %p\n", i, q->data[(q->front + i) % q->capacity]);
    }
}
