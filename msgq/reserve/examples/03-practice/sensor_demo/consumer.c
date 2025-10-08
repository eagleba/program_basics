#include "common.h"

int main() {
    printf("=== OLED显示消费者启动 ===\n");
    
    // 初始化ZeroMQ
    void *context = zmq_ctx_new();
    void *socket = zmq_socket(context, ZMQ_PULL);
    
    // 绑定端口等待生产者连接
    int rc = zmq_bind(socket, "tcp://*:5555");
    if (rc != 0) {
        printf("绑定失败！\n");
        zmq_close(socket);
        zmq_ctx_destroy(context);
        return -1;
    }
    
    printf("已绑定端口 5555，等待生产者连接...\n");
    printf("开始接收传感器数据...\n\n");
    
    int message_count = 0;
    while (1) {
        sensor_message_t msg;
        
        // 接收消息
        rc = zmq_recv(socket, &msg, sizeof(msg), 0);
        if (rc == sizeof(msg)) {
            message_count++;
            printf("[消费者] 接收消息 #%d: 传感器ID=%d, 值=%.2f, 时间戳=%u\n", 
                   message_count, msg.sensor_id, msg.value, msg.timestamp);
            
            // 根据传感器类型显示数据
            if (msg.sensor_id == TEMP_SENSOR_ID) {
                oled_display_temperature(msg.value);
            } else if (msg.sensor_id == HUMIDITY_SENSOR_ID) {
                oled_display_humidity(msg.value);
            }
            
            printf("---\n");
        } else {
            printf("[消费者] 接收失败！\n");
        }
    }
    
    // 清理资源
    zmq_close(socket);
    zmq_ctx_destroy(context);
    return 0;
}
