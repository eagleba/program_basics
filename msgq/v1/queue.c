#include "queue.h"
#include <string.h>

// 队列结构体已在头文件中定义

// 配置参数
#define MAX_QUEUES 8
#define MAX_QUEUE_SIZE 64

// 静态内存池
static Queue static_queues[MAX_QUEUES];
static void *static_buffers[MAX_QUEUES][MAX_QUEUE_SIZE];
static bool queue_used[MAX_QUEUES] = {false};

// 版本信息
static const char *version = "1.0.0";

// ========== 核心API实现 ==========

Queue *queue_create(uint16_t size) {
    // 参数验证
    if (size == 0 || size > MAX_QUEUE_SIZE) {
        return NULL;
    }
    
    // 找到空闲的队列
    for (int i = 0; i < MAX_QUEUES; i++) {
        if (!queue_used[i]) {
            queue_used[i] = true;
            
            // 初始化队列
            static_queues[i].buffer = static_buffers[i];
            static_queues[i].size = size;
            static_queues[i].head = 0;
            static_queues[i].tail = 0;
            static_queues[i].count = 0;
            
            // 清理缓冲区
            memset(static_buffers[i], 0, size * sizeof(void*));
            
            return &static_queues[i];
        }
    }
    
    return NULL; // 没有空闲队列
}

void queue_destroy(Queue *queue) {
    if (queue == NULL) return;
    
    // 找到队列索引并标记为未使用
    for (int i = 0; i < MAX_QUEUES; i++) {
        if (&static_queues[i] == queue) {
            queue_used[i] = false;
            queue_clear(queue);
            break;
        }
    }
}

bool queue_enqueue(Queue *queue, void *item) {
    if (queue == NULL || item == NULL || queue_is_full(queue)) {
        return false;
    }
    
    // Store pointer directly
    queue->buffer[queue->tail] = item;
    
    // Update tail pointer and count
    queue->tail = (queue->tail + 1) % queue->size;
    queue->count++;
    
    return true;
}

bool queue_dequeue(Queue *queue, void **item) {
    if (queue == NULL || item == NULL || queue_is_empty(queue)) {
        return false;
    }
    
    // Return pointer directly
    *item = queue->buffer[queue->head];
    
    // Update head pointer and count
    queue->head = (queue->head + 1) % queue->size;
    queue->count--;
    
    return true;
}

bool queue_is_full(const Queue *queue) {
    return (queue != NULL) && (queue->count >= queue->size);
}

bool queue_is_empty(const Queue *queue) {
    return (queue != NULL) && (queue->count == 0);
}

uint16_t queue_get_count(const Queue *queue) {
    return (queue != NULL) ? queue->count : 0;
}

void queue_clear(Queue *queue) {
    if (queue != NULL) {
        queue->head = 0;
        queue->tail = 0;
        queue->count = 0;
        memset(queue->buffer, 0, queue->size * sizeof(void*));
    }
}

// ========== 高级API实现 ==========

bool queue_init(Queue *queue, void **buffer, uint16_t size) {
    if (queue == NULL || buffer == NULL || size == 0) {
        return false;
    }
    
    queue->buffer = buffer;
    queue->size = size;
    queue->head = 0;
    queue->tail = 0;
    queue->count = 0;
    
    // 清理缓冲区
    memset(buffer, 0, size * sizeof(void*));
    
    return true;
}

const char *queue_get_version(void) {
    return version;
}

size_t queue_get_memory_usage(void) {
    return sizeof(static_queues) + sizeof(static_buffers);
}

int queue_get_available_queues(void) {
    int count = 0;
    for (int i = 0; i < MAX_QUEUES; i++) {
        if (!queue_used[i]) {
            count++;
        }
    }
    return count;
}
