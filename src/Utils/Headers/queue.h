#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

typedef int QueueData; // Por ahora está con INT

typedef struct Queue Queue;

Queue* queue_create();
void queue_destroy(Queue* q);
bool queue_is_empty(const Queue* q);
bool queue_is_full(const Queue* q);
void queue_enqueue(Queue* q, QueueData value);
QueueData queue_dequeue(Queue* q);

#endif
