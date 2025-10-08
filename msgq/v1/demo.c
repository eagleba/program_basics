#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

// 消息结构体
typedef struct {
    uint8_t sensor_id;
    float value;
    uint32_t timestamp;
} sensor_message_t;

int main() {
    printf("=== Queue v1 Demo Program ===\n");
    printf("Version: %s\n", queue_get_version());
    printf("Memory usage: %zu bytes\n", queue_get_memory_usage());
    printf("Available queues: %d\n", queue_get_available_queues());
    printf("\n");
    
    // 创建队列
    Queue *queue = queue_create(5);
    if (queue == NULL) {
        printf("Failed to create queue!\n");
        return -1;
    }
    
    printf("Queue created successfully\n");
    printf("Available queues after creation: %d\n", queue_get_available_queues());
    printf("\n");
    
    // 测试入队操作
    printf("=== Testing Enqueue Operations ===\n");
    sensor_message_t messages[7];  // Pre-allocated message array
    
    for (int i = 0; i < 7; i++) {  // Try to enqueue 7 messages, but queue can only hold 5
        // Fill message data
        messages[i].sensor_id = 1;
        messages[i].value = 25.5 + i;
        messages[i].timestamp = 1000 + i;
        
        if (queue_enqueue(queue, &messages[i])) {
            printf("Enqueue success: Sensor ID=%d, Value=%.1f, Timestamp=%u\n", 
                   messages[i].sensor_id, messages[i].value, messages[i].timestamp);
        } else {
            printf("Enqueue failed: Queue is full!\n");
        }
        
        printf("Current queue message count: %d\n", queue_get_count(queue));
    }
    
    // 测试出队操作
    printf("\n=== Testing Dequeue Operations ===\n");
    while (!queue_is_empty(queue)) {
        sensor_message_t *msg_ptr;
        if (queue_dequeue(queue, (void**)&msg_ptr)) {
            printf("Dequeue success: Sensor ID=%d, Value=%.1f, Timestamp=%u\n", 
                   msg_ptr->sensor_id, msg_ptr->value, msg_ptr->timestamp);
        }
        printf("Current queue message count: %d\n", queue_get_count(queue));
    }
    
    // 测试空队列出队
    printf("\n=== Testing Dequeue from Empty Queue ===\n");
    sensor_message_t *msg_ptr;
    if (!queue_dequeue(queue, (void**)&msg_ptr)) {
        printf("Dequeue failed: Queue is empty!\n");
    }
    
    // 测试静态分配模式
    printf("\n=== Testing Static Allocation Mode ===\n");
    QUEUE_DECLARE(static_queue, 3);
    if (!QUEUE_INIT(static_queue, 3)) {
        printf("Failed to initialize static queue!\n");
    } else {
        printf("Static queue initialized successfully\n");
        
        // 测试静态队列
        sensor_message_t test_msg = {2, 30.0, 2000};
        if (queue_enqueue(&static_queue, &test_msg)) {
            printf("Static queue enqueue success\n");
        }
        
        sensor_message_t *received;
        if (queue_dequeue(&static_queue, (void**)&received)) {
            printf("Static queue dequeue success: Value=%.1f\n", received->value);
        }
    }
    
    // 清理
    printf("\n=== Cleanup ===\n");
    queue_destroy(queue);
    printf("Queue destroyed\n");
    printf("Available queues after destruction: %d\n", queue_get_available_queues());
    
    printf("\n=== Demo Complete ===\n");
    return 0;
}
