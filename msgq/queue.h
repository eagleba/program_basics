#ifndef QUEUE_H
#define QUEUE_H

#include <stdint.h>
#include <stdbool.h>

// 队列结构体（客户不需要直接操作）
typedef struct {
    void **buffer;        // Queue buffer (stores pointers)
    uint16_t head;        // Queue head pointer
    uint16_t tail;        // Queue tail pointer
    uint16_t size;        // Queue size
    uint16_t count;       // Current message count
} Queue;

// ========== 核心API ==========

// 创建和销毁
Queue *queue_create(uint16_t size);
void queue_destroy(Queue *queue);

// 基本操作
bool queue_enqueue(Queue *queue, void *item);
bool queue_dequeue(Queue *queue, void **item);

// 状态查询
bool queue_is_empty(const Queue *queue);
bool queue_is_full(const Queue *queue);
uint16_t queue_get_count(const Queue *queue);

// 工具函数
void queue_clear(Queue *queue);

// ========== 高级API ==========

// 静态分配模式
bool queue_init(Queue *queue, void **buffer, uint16_t size);

// 系统信息
const char *queue_get_version(void);
size_t queue_get_memory_usage(void);
int queue_get_available_queues(void);

// ========== 便利宏 ==========

// 简化静态分配
#define QUEUE_DECLARE(name, size) \
    void *name##_buffer[size]; \
    Queue name

#define QUEUE_INIT(name, size) \
    queue_init(&name, name##_buffer, size)

#endif // QUEUE_H
