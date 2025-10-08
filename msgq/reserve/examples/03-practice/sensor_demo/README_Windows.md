# Windows环境编译和运行指南

## 环境准备

### 1. 安装MinGW-w64编译器

**方法一：使用MSYS2（推荐）**
1. 下载MSYS2：https://www.msys2.org/
2. 安装后打开MSYS2终端
3. 更新包管理器：
   ```bash
   pacman -Syu
   ```
4. 安装MinGW-w64：
   ```bash
   pacman -S mingw-w64-x86_64-gcc
   pacman -S mingw-w64-x86_64-make
   ```

**方法二：直接下载MinGW-w64**
1. 访问：https://www.mingw-w64.org/downloads/
2. 下载Windows版本
3. 解压到 `C:\mingw64`
4. 将 `C:\mingw64\bin` 添加到系统PATH

### 2. 安装ZeroMQ库

**方法一：使用vcpkg（推荐）**
1. 安装vcpkg：
   ```cmd
   git clone https://github.com/Microsoft/vcpkg.git
   cd vcpkg
   .\bootstrap-vcpkg.bat
   ```
2. 安装ZeroMQ：
   ```cmd
   .\vcpkg install zeromq:x64-windows
   ```

**方法二：预编译版本**
1. 下载ZeroMQ Windows版本：https://github.com/zeromq/libzmq/releases
2. 解压到 `C:\zmq`
3. 确保目录结构如下：
   ```
   C:\zmq\
   ├── include\
   │   └── zmq.h
   └── lib\
       ├── libzmq.lib
       └── libzmq.dll
   ```

## 编译和运行

### 简单队列演示（无需ZeroMQ）

1. 打开命令提示符，进入项目目录：
   ```cmd
   cd msgq\examples\02-principles
   ```

2. 运行编译脚本：
   ```cmd
   build.bat
   ```

3. 或者手动编译：
   ```cmd
   gcc -Wall -Wextra -std=c99 -O2 -o queue_demo.exe simple_queue.c queue_demo.c
   queue_demo.exe
   ```

### ZeroMQ传感器演示

1. 确保已安装ZeroMQ库

2. 进入项目目录：
   ```cmd
   cd msgq\examples\03-practice\sensor_demo
   ```

3. 运行编译脚本：
   ```cmd
   build_windows.bat
   ```

4. 运行演示：
   - 打开两个命令提示符窗口
   - 窗口1：`consumer.exe`
   - 窗口2：`producer.exe`

## 使用Visual Studio

### 创建项目
1. 打开Visual Studio
2. 创建新的"控制台应用程序"项目
3. 添加源文件到项目

### 配置ZeroMQ
1. 右键项目 → 属性
2. C/C++ → 常规 → 附加包含目录：添加ZeroMQ的include路径
3. 链接器 → 常规 → 附加库目录：添加ZeroMQ的lib路径
4. 链接器 → 输入 → 附加依赖项：添加 `libzmq.lib`

### 编译设置
- 平台：x64
- 配置：Debug或Release
- C++标准：C99

## 常见问题

### 1. "gcc不是内部或外部命令"
- 检查MinGW是否正确安装
- 确认PATH环境变量包含MinGW的bin目录

### 2. "zmq.h: No such file or directory"
- 检查ZeroMQ是否正确安装
- 确认头文件路径正确

### 3. "undefined reference to zmq_*"
- 检查链接库路径
- 确认libzmq.lib文件存在

### 4. 运行时找不到DLL
- 将ZeroMQ的bin目录添加到PATH
- 或将libzmq.dll复制到exe同目录

## 替代方案

如果ZeroMQ安装困难，可以使用以下替代方案：

### 1. 使用Windows Socket API
```c
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
```

### 2. 使用简单的文件队列
```c
// 使用文件作为消息队列
FILE *queue_file = fopen("message_queue.dat", "ab+");
```

### 3. 使用Windows消息队列
```c
#include <windows.h>
// 使用Windows消息机制
```

## 性能优化

### 编译优化
```cmd
gcc -O3 -march=native -mtune=native -o program.exe source.c
```

### 运行时优化
- 使用Release版本
- 关闭调试输出
- 优化网络缓冲区大小
