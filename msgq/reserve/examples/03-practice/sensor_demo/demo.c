/*
 * 简化的Windows消息队列演示
 * 不依赖ZeroMQ，使用简单的文件队列实现
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <windows.h>

// 消息结构体
typedef struct {
    uint8_t sensor_id;
    float value;
    uint32_t timestamp;
} sensor_message_t;

// 队列文件路径
#define QUEUE_FILE "message_queue.dat"
#define MAX_MESSAGES 100

// 模拟传感器读取
float read_temperature_sensor(void) {
    static float base_temp = 25.0;
    base_temp += (rand() % 100 - 50) / 100.0;
    if (base_temp < 20.0) base_temp = 20.0;
    if (base_temp > 30.0) base_temp = 30.0;
    return base_temp;
}

// 写入消息到队列文件
int write_message(const sensor_message_t *msg) {
    FILE *fp = fopen(QUEUE_FILE, "ab");
    if (fp == NULL) return 0;
    
    int result = fwrite(msg, sizeof(sensor_message_t), 1, fp);
    fclose(fp);
    return result;
}

// 从队列文件读取消息
int read_message(sensor_message_t *msg) {
    FILE *fp = fopen(QUEUE_FILE, "rb");
    if (fp == NULL) return 0;
    
    int result = fread(msg, sizeof(sensor_message_t), 1, fp);
    fclose(fp);
    return result;
}

// 清空队列文件
void clear_queue(void) {
    FILE *fp = fopen(QUEUE_FILE, "wb");
    if (fp) fclose(fp);
}

// 生产者模式
void run_producer(void) {
    printf("=== 生产者模式 ===\n");
    printf("按Ctrl+C停止\n\n");
    
    int count = 0;
    while (1) {
        sensor_message_t msg = {
            .sensor_id = 1,
            .value = read_temperature_sensor(),
            .timestamp = (uint32_t)time(NULL)
        };
        
        if (write_message(&msg)) {
            count++;
            printf("[生产者] 发送消息 #%d: 温度=%.2f°C\n", count, msg.value);
        }
        
        Sleep(1000);  // 1秒间隔
    }
}

// 消费者模式
void run_consumer(void) {
    printf("=== 消费者模式 ===\n");
    printf("按Ctrl+C停止\n\n");
    
    int count = 0;
    while (1) {
        sensor_message_t msg;
        
        if (read_message(&msg)) {
            count++;
            printf("[消费者] 接收消息 #%d: 传感器ID=%d, 温度=%.2f°C, 时间=%u\n", 
                   count, msg.sensor_id, msg.value, msg.timestamp);
            
            // 模拟OLED显示
            printf("[OLED] 显示温度: %.2f°C\n", msg.value);
            printf("---\n");
            
            // 清空已读消息
            clear_queue();
        }
        
        Sleep(100);  // 100ms检查一次
    }
}

int main(int argc, char *argv[]) {
    srand((unsigned int)time(NULL));
    
    printf("Windows简化消息队列演示\n");
    printf("======================\n\n");
    
    if (argc < 2) {
        printf("用法：\n");
        printf("  %s producer  - 运行生产者\n", argv[0]);
        printf("  %s consumer  - 运行消费者\n", argv[0]);
        printf("\n注意：请先运行消费者，再运行生产者\n");
        return 1;
    }
    
    if (strcmp(argv[1], "producer") == 0) {
        run_producer();
    } else if (strcmp(argv[1], "consumer") == 0) {
        run_consumer();
    } else {
        printf("错误：未知参数 '%s'\n", argv[1]);
        printf("请使用 'producer' 或 'consumer'\n");
        return 1;
    }
    
    return 0;
}
