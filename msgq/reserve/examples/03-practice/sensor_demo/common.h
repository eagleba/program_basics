#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <zmq.h>

// 消息类型定义
#define TEMP_SENSOR_ID 1
#define HUMIDITY_SENSOR_ID 2

// 消息结构体
typedef struct {
    uint8_t sensor_id;    // 传感器ID
    float value;          // 数据值
    uint32_t timestamp;   // 时间戳
} sensor_message_t;

// 模拟传感器读取函数
float read_temperature_sensor(void);
float read_humidity_sensor(void);

// 模拟OLED显示函数
void oled_display_temperature(float temp);
void oled_display_humidity(float humidity);

// 模拟蓝牙发送函数
void bluetooth_send_data(const sensor_message_t *msg);

// 工具函数
uint32_t get_timestamp(void);
void delay_ms(int ms);

#endif // COMMON_H
