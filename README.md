# IPC 编程基础 - 进程间通信实践

一个基于 C 语言的 IPC（进程间通信）学习项目，提供统一的 IPC 抽象接口，支持多种底层实现方式。

## 🎯 项目特点

- ✅ **统一接口**：提供统一的 IPC API，调用者无需关心底层实现
- ✅ **模块化设计**：清晰的目录结构，职责明确
- ✅ **多种实现**：支持消息队列、管道等多种 IPC 方式
- ✅ **实际场景**：提供客户端-服务器等真实应用场景测试
- ✅ **易于扩展**：可轻松添加新的 IPC 实现和测试场景

## 📁 项目结构

```
program_basics/
├── include/              # 公共头文件
│   └── ipc.h            # 统一的 IPC 接口定义
│
├── lib/                 # 编译后的库文件
│   └── libmsgq.a       # 消息队列实现库
│
├── msgq/                # 消息队列模块
│   ├── queue.h/c       # 底层队列实现
│   ├── msgq_ipc.c      # IPC 接口适配层
│   └── Makefile        # 构建静态库
│
├── pipe/                # 管道模块（待实现）
│   └── ...
│
├── test/                # 测试代码
│   └── client_server/  # 客户端-服务器测试
│       ├── test_client_server.c
│       ├── test_file.txt
│       └── Makefile
│
├── Makefile            # 顶层 Makefile
├── .gitignore          # Git 忽略配置
└── README.md           # 本文件
```

## 🔧 IPC 统一接口设计

### 核心思想

调用者只需了解通用的 IPC API，底层实现由链接的库决定：

```c
应用代码
   ↓
ipc.h (统一接口)
   ↓
[链接时选择]
   ↓
├─ msgq/msgq_ipc.c → libmsgq.a  (消息队列实现)
└─ pipe/pipe_ipc.c → libpipe.a  (管道实现)
```

### 接口示例

```c
// 创建 IPC 通道
IPC_Handle ipc_create(size_t capacity);

// 发送数据
bool ipc_send(IPC_Handle handle, void *data);

// 接收数据
bool ipc_recv(IPC_Handle handle, void **data);

// 销毁通道
void ipc_destroy(IPC_Handle handle);

// 获取实现类型
const char* ipc_get_type(void);
```

## 🚀 快速开始

### 环境要求

- **编译器**：GCC (MinGW-w64 on Windows)
- **构建工具**：mingw32-make
- **操作系统**：Windows / Linux

### 编译项目

```bash
# 编译所有库和测试
mingw32-make

# 或分步骤编译
mingw32-make lib      # 只编译库
mingw32-make test     # 只编译测试
```

### 运行测试

```bash
# 运行客户端-服务器测试
mingw32-make run-test

# 手动运行
cd test\client_server
.\test_client_server_msgq.exe
# 输入文件名，例如：test_file.txt
```

### 清理

```bash
mingw32-make clean
```

## 📝 测试场景说明

### 1. 客户端-服务器模型 (test/client_server/)

**场景描述：** 实现一个简单的文件服务器

**工作流程：**
```
1. 服务器创建接收队列，等待请求
2. 客户端创建接收队列，发送文件名请求
3. 服务器读取文件内容，发送响应
4. 客户端接收并打印文件内容
```

**特点：**
- 每个线程拥有自己的接收队列
- 清晰的 API 封装（server_init, client_init 等）
- 演示双向通信

**运行示例：**
```
[Server] Created my receive queue
[Client] Created my receive queue
[Client] Enter filename: test_file.txt
[Server] Received request for file: test_file.txt
[Server] Read 357 bytes from file
========== File Content ==========
Hello, this is a test file...
========== End (Total: 357 bytes) ==========
```

## 🎨 设计理念

### 1. 模块职责分离

- **msgq/**: 只负责消息队列的核心实现
- **pipe/**: 只负责管道的核心实现
- **test/**: 按应用场景分类测试
- **include/**: 统一的接口定义

### 2. 接口与实现分离

```c
// 统一接口 (include/ipc.h)
IPC_Handle ipc_create(size_t capacity);

// 消息队列实现 (msgq/msgq_ipc.c)
IPC_Handle ipc_create(size_t capacity) {
    return (IPC_Handle)queue_create((uint16_t)capacity);
}

// 管道实现 (pipe/pipe_ipc.c)
IPC_Handle ipc_create(size_t capacity) {
    return (IPC_Handle)bipipe_create();
}
```

### 3. 测试驱动

每个测试场景都是一个独立的应用案例：
- **client_server**: 文件服务器
- **producer_consumer**: 生产者消费者（待实现）
- **request_response**: 请求响应模式（待实现）

## 🔍 Makefile 架构

### 层级结构

```
顶层 Makefile
  ↓
├─ msgq/Makefile    → 生成 lib/libmsgq.a
├─ pipe/Makefile    → 生成 lib/libpipe.a (待实现)
└─ test/*/Makefile  → 链接库生成测试程序
```

### 常用命令

```bash
mingw32-make           # 构建所有
mingw32-make lib       # 只构建库
mingw32-make test      # 只构建测试
mingw32-make run-test  # 运行测试
mingw32-make clean     # 清理
mingw32-make help      # 显示帮助
```

## 📚 代码示例

### 使用统一接口编写代码

```c
#include "ipc.h"

int main() {
    // 创建通道（底层可能是队列或管道）
    IPC_Handle ipc = ipc_create(10);
    
    printf("Using: %s\n", ipc_get_type());
    
    // 发送数据
    int *data = malloc(sizeof(int));
    *data = 42;
    ipc_send(ipc, data);
    
    // 接收数据
    int *received;
    ipc_recv(ipc, (void**)&received);
    printf("Received: %d\n", *received);
    
    // 清理
    ipc_destroy(ipc);
    return 0;
}
```

### 编译选择不同实现

```bash
# 使用消息队列
gcc test.c -I./include -L./lib -lmsgq -o test_msgq

# 使用管道（未来）
gcc test.c -I./include -L./lib -lpipe -o test_pipe
```

## 🚧 后续计划

- [ ] 实现 pipe 模块（双向管道 IPC）
- [ ] 添加 producer_consumer 测试场景
- [ ] 添加 request_response 测试场景
- [ ] 添加性能基准测试
- [ ] 支持共享内存 IPC
- [ ] 支持 socket IPC

## ⚠️ 注意事项

1. **编译产物**：`.o`, `.a`, `.exe` 文件已在 `.gitignore` 中忽略
2. **小文件限制**：当前测试假设文件小于 64KB
3. **Windows 平台**：部分代码使用 Windows 特定 API
4. **线程安全**：当前实现为单客户端场景

## 💡 学习建议

1. **从接口开始**：先看 `include/ipc.h` 了解抽象接口
2. **阅读实现**：对比 `msgq/msgq_ipc.c` 如何实现接口
3. **运行测试**：通过 `test/client_server` 理解实际应用
4. **修改扩展**：尝试添加新功能或优化现有代码

## 📖 参考资料

- [POSIX 消息队列](https://man7.org/linux/man-pages/man7/mq_overview.7.html)
- [管道通信](https://man7.org/linux/man-pages/man2/pipe.2.html)
- [进程间通信（IPC）概述](https://en.wikipedia.org/wiki/Inter-process_communication)

---

**项目作者：** Program Basics Study  
**最后更新：** 2025-10-12
