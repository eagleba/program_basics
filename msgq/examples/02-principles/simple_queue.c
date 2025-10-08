#include "simple_queue.h"
#include <string.h>

// Initialize queue
bool queue_init(Queue *q, void **buffer, uint16_t size) {
    if (q == NULL || buffer == NULL || size == 0) {
        return false;
    }
    
    q->buffer = buffer;
    q->size = size;
    q->head = 0;
    q->tail = 0;
    q->count = 0;
    
    return true;
}

// Enqueue operation
bool queue_enqueue(Queue *q, void *item) {
    if (q == NULL || item == NULL || queue_is_full(q)) {
        return false;
    }
    
    // Store pointer directly
    q->buffer[q->tail] = item;
    
    // Update tail pointer and count
    q->tail = (q->tail + 1) % q->size;
    q->count++;
    
    return true;
}

// Dequeue operation
bool queue_dequeue(Queue *q, void **item) {
    if (q == NULL || item == NULL || queue_is_empty(q)) {
        return false;
    }
    
    // Return pointer directly
    *item = q->buffer[q->head];
    
    // Update head pointer and count
    q->head = (q->head + 1) % q->size;
    q->count--;
    
    return true;
}

// Check if queue is full
bool queue_is_full(const Queue *q) {
    return (q != NULL) && (q->count >= q->size);
}

// Check if queue is empty
bool queue_is_empty(const Queue *q) {
    return (q != NULL) && (q->count == 0);
}

// Get current message count
uint16_t queue_get_count(const Queue *q) {
    return (q != NULL) ? q->count : 0;
}

// Clear queue
void queue_clear(Queue *q) {
    if (q != NULL) {
        q->head = 0;
        q->tail = 0;
        q->count = 0;
    }
}
