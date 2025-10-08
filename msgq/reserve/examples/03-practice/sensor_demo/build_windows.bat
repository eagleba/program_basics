@echo off
echo === Windows ZeroMQ项目编译脚本 ===

REM 检查是否安装了MinGW
where gcc >nul 2>&1
if %errorlevel% neq 0 (
    echo 错误：未找到gcc编译器！
    echo 请安装MinGW-w64或MSYS2
    echo 下载地址：https://www.msys2.org/
    pause
    exit /b 1
)

REM 检查ZeroMQ库
if not exist "C:\zmq\include\zmq.h" (
    echo 错误：未找到ZeroMQ库！
    echo 请按照README_Windows.md的说明安装ZeroMQ
    pause
    exit /b 1
)

echo 找到编译环境，开始编译...

REM 编译生产者
echo 编译生产者...
gcc -Wall -Wextra -std=c99 -O2 -I"C:\zmq\include" -o producer.exe producer.c common.c -L"C:\zmq\lib" -lzmq -lws2_32 -lwsock32

if %errorlevel% neq 0 (
    echo 生产者编译失败！
    pause
    exit /b 1
)

REM 编译消费者
echo 编译消费者...
gcc -Wall -Wextra -std=c99 -O2 -I"C:\zmq\include" -o consumer.exe consumer.c common.c -L"C:\zmq\lib" -lzmq -lws2_32 -lwsock32

if %errorlevel% neq 0 (
    echo 消费者编译失败！
    pause
    exit /b 1
)

echo 编译成功！
echo.
echo 运行说明：
echo 1. 打开两个命令提示符窗口
echo 2. 在第一个窗口运行：consumer.exe
echo 3. 在第二个窗口运行：producer.exe

pause
