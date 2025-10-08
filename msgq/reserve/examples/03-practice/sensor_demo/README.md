# 传感器数据传输演示

这是一个使用ZeroMQ实现的单生产者-单消费者消息队列演示程序。

## 项目结构

```
sensor_demo/
├── Makefile          # 编译脚本
├── common.h          # 公共头文件
├── common.c          # 公共函数实现
├── producer.c        # 生产者（传感器数据）
├── consumer.c        # 消费者（OLED显示）
└── README.md         # 说明文档
```

## 功能说明

- **生产者**：模拟温度传感器，每100ms发送一次数据
- **消费者**：接收数据并在OLED上显示（实际是打印到控制台）

## 编译和运行

### 1. 编译程序

```bash
make all
```

### 2. 运行演示

需要打开两个终端：

**终端1 - 启动消费者：**
```bash
make run-consumer
```

**终端2 - 启动生产者：**
```bash
make run-producer
```

### 3. 预期效果

- 生产者会持续发送温度数据
- 消费者会接收数据并显示
- 可以看到实时的数据传输过程

## 依赖要求

- ZeroMQ库 (libzmq)
- GCC编译器
- Linux/Unix系统

## 安装ZeroMQ

### Ubuntu/Debian:
```bash
sudo apt-get install libzmq3-dev
```

### CentOS/RHEL:
```bash
sudo yum install zeromq-devel
```

### 从源码编译:
```bash
git clone https://github.com/zeromq/libzmq.git
cd libzmq
./configure
make && sudo make install
```

## 故障排除

1. **编译错误 "zmq.h: No such file"**
   - 确保已安装ZeroMQ开发库
   - 检查pkg-config路径

2. **运行时错误 "Address already in use"**
   - 检查端口5555是否被占用
   - 先启动消费者，再启动生产者

3. **连接失败**
   - 确保消费者已启动并绑定端口
   - 检查防火墙设置
