#include <stdlib.h>
#include <stdio.h>
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
    q->capacity = INITIAL_CAPACITY;
    q->data = malloc(q->capacity * sizeof(QueueData));
    q->front = 0;
    q->rear = -1;
    q->size = 0;
    return q;
}

void queue_destroy(Queue* q) {
    if (q) {
        free(q->data);
        free(q);
    }
}

bool queue_is_empty(const Queue* q) {
    return q->size == 0;
}

bool queue_is_full(const Queue* q) {
    return q->size == q->capacity;
}

void queue_enqueue(Queue* q, QueueData value) {
    if (queue_is_full(q)) {
        int new_capacity = q->capacity * 2;
        QueueData* new_data = malloc(new_capacity * sizeof(QueueData));
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
    if (queue_is_empty(q)) {
        fprintf(stderr, "Queue underflow\n");
        exit(EXIT_FAILURE);
    }
    QueueData value = q->data[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return value;
}
