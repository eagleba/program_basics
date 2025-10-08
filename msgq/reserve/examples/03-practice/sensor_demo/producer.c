#include "common.h"

int main() {
    printf("=== 传感器数据生产者启动 ===\n");
    
    // 初始化随机数种子
    srand(time(NULL));
    
    // 初始化ZeroMQ
    void *context = zmq_ctx_new();
    void *socket = zmq_socket(context, ZMQ_PUSH);
    
    // 连接到消费者
    int rc = zmq_connect(socket, "tcp://localhost:5555");
    if (rc != 0) {
        printf("连接失败！\n");
        zmq_close(socket);
        zmq_ctx_destroy(context);
        return -1;
    }
    
    printf("已连接到消费者 (tcp://localhost:5555)\n");
    printf("开始发送传感器数据...\n\n");
    
    int message_count = 0;
    while (1) {
        // 读取传感器数据
        float temperature = read_temperature_sensor();
        
        // 构造消息
        sensor_message_t msg = {
            .sensor_id = TEMP_SENSOR_ID,
            .value = temperature,
            .timestamp = get_timestamp()
        };
        
        // 发送消息
        rc = zmq_send(socket, &msg, sizeof(msg), 0);
        if (rc == sizeof(msg)) {
            message_count++;
            printf("[生产者] 发送消息 #%d: 温度=%.2f°C, 时间戳=%u\n", 
                   message_count, msg.value, msg.timestamp);
        } else {
            printf("[生产者] 发送失败！\n");
        }
        
        // 延时100ms
        delay_ms(100);
    }
    
    // 清理资源
    zmq_close(socket);
    zmq_ctx_destroy(context);
    return 0;
}
