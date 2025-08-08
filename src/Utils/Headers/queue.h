#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stddef.h>

// Alias para datos genéricos en la cola
typedef void* QueueData;

// Definición opaca de la estructura
typedef struct Queue Queue;

// Crea una cola vacía
Queue* queue_create();

// Destruye la cola.
// Si free_data es true, se libera cada elemento (útil si los datos son punteros a memoria dinámica).
void queue_destroy(Queue* q, bool free_data);

// Retorna true si la cola está vacía.
bool queue_is_empty(const Queue* q);

// Retorna true si la cola está llena (antes de expandirse).
bool queue_is_full(const Queue* q);

// Inserta un elemento al final de la cola.
void queue_enqueue(Queue* q, QueueData value);

// Extrae el primer elemento de la cola.
// Si está vacía, imprime error y finaliza el programa.
QueueData queue_dequeue(Queue* q);

// Devuelve el primer elemento sin extraerlo (NULL si está vacía).
QueueData queue_peek(const Queue* q);

// Función opcional para depuración: imprime direcciones y conteo.
void queue_debug_print(const Queue* q);

#endif
