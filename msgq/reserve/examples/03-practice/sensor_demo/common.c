#include "common.h"
#include <math.h>

#ifdef _WIN32
#include <windows.h>
#define usleep(x) Sleep((x)/1000)
#else
#include <unistd.h>
#endif

// 模拟温度传感器读取
float read_temperature_sensor(void) {
    // 模拟温度在20-30度之间波动
    static float base_temp = 25.0;
    base_temp += (rand() % 100 - 50) / 100.0;  // ±0.5度波动
    if (base_temp < 20.0) base_temp = 20.0;
    if (base_temp > 30.0) base_temp = 30.0;
    return base_temp;
}

// 模拟湿度传感器读取
float read_humidity_sensor(void) {
    // 模拟湿度在40-80%之间波动
    static float base_humidity = 60.0;
    base_humidity += (rand() % 100 - 50) / 100.0;  // ±0.5%波动
    if (base_humidity < 40.0) base_humidity = 40.0;
    if (base_humidity > 80.0) base_humidity = 80.0;
    return base_humidity;
}

// 模拟OLED显示温度
void oled_display_temperature(float temp) {
    printf("[OLED] 温度: %.2f°C\n", temp);
}

// 模拟OLED显示湿度
void oled_display_humidity(float humidity) {
    printf("[OLED] 湿度: %.2f%%\n", humidity);
}

// 模拟蓝牙发送数据
void bluetooth_send_data(const sensor_message_t *msg) {
    printf("[蓝牙] 发送数据: ID=%d, 值=%.2f, 时间=%u\n", 
           msg->sensor_id, msg->value, msg->timestamp);
}

// 获取时间戳
uint32_t get_timestamp(void) {
    return (uint32_t)time(NULL);
}

// 延时函数
void delay_ms(int ms) {
#ifdef _WIN32
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}
