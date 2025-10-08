#ifndef SIMPLE_QUEUE_H
#define SIMPLE_QUEUE_H

#include <stdint.h>
#include <stdbool.h>

// Queue structure definition
typedef struct {
    void **buffer;        // Queue buffer (stores pointers)
    uint16_t head;        // Queue head pointer
    uint16_t tail;        // Queue tail pointer
    uint16_t size;        // Queue size
    uint16_t count;       // Current message count
} Queue;

// Queue operation function declarations
bool queue_init(Queue *q, void **buffer, uint16_t size);
bool queue_enqueue(Queue *q, void *item);
bool queue_dequeue(Queue *q, void **item);
bool queue_is_full(const Queue *q);
bool queue_is_empty(const Queue *q);
uint16_t queue_get_count(const Queue *q);
void queue_clear(Queue *q);

#endif // SIMPLE_QUEUE_H