#include <stdio.h>
#include <stdlib.h>
#include "simple_queue.h"

// 定义消息结构体
typedef struct {
    uint8_t sensor_id;
    float value;
    uint32_t timestamp;
} sensor_message_t;

int main() {
    printf("=== Simple Queue Demo Program ===\n");
    
    // Define queue buffer (stores pointers)
    #define QUEUE_SIZE 5
    void *buffer[QUEUE_SIZE];
    
    // Initialize queue
    Queue queue;
    if (!queue_init(&queue, buffer, QUEUE_SIZE)) {
        printf("Queue initialization failed!\n");
        return -1;
    }
    
    printf("Queue initialized successfully, size: %d, storing pointers\n", QUEUE_SIZE);
    
    // Test enqueue operations
    printf("\n=== Testing Enqueue Operations ===\n");
    sensor_message_t messages[7];  // Pre-allocated message array
    
    for (int i = 0; i < 7; i++) {  // Try to enqueue 7 messages, but queue can only hold 5
        // Fill message data
        messages[i].sensor_id = 1;
        messages[i].value = 25.5 + i;
        messages[i].timestamp = 1000 + i;
        
        if (queue_enqueue(&queue, &messages[i])) {
            printf("Enqueue success: Sensor ID=%d, Value=%.1f, Timestamp=%u\n", 
                   messages[i].sensor_id, messages[i].value, messages[i].timestamp);
        } else {
            printf("Enqueue failed: Queue is full!\n");
        }
        
        printf("Current queue message count: %d\n", queue_get_count(&queue));
    }
    
    // Test dequeue operations
    printf("\n=== Testing Dequeue Operations ===\n");
    while (!queue_is_empty(&queue)) {
        sensor_message_t *msg_ptr;
        if (queue_dequeue(&queue, (void**)&msg_ptr)) {
            printf("Dequeue success: Sensor ID=%d, Value=%.1f, Timestamp=%u\n", 
                   msg_ptr->sensor_id, msg_ptr->value, msg_ptr->timestamp);
        }
        printf("Current queue message count: %d\n", queue_get_count(&queue));
    }
    
    // Test dequeue from empty queue
    printf("\n=== Testing Dequeue from Empty Queue ===\n");
    sensor_message_t *msg_ptr;
    if (!queue_dequeue(&queue, (void**)&msg_ptr)) {
        printf("Dequeue failed: Queue is empty!\n");
    }
    
    printf("\n=== Demo Complete ===\n");
    return 0;
}
