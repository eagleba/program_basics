@echo off
echo === Windows简化版消息队列演示 ===

REM 检查是否安装了MinGW
where gcc >nul 2>&1
if %errorlevel% neq 0 (
    echo 错误：未找到gcc编译器！
    echo 请安装MinGW-w64或MSYS2
    echo 下载地址：https://www.msys2.org/
    pause
    exit /b 1
)

echo 找到gcc编译器，开始编译...

REM 编译简化版演示程序
gcc -Wall -Wextra -std=c99 -O2 -o simple_demo.exe simple_windows_demo.c

if %errorlevel% equ 0 (
    echo 编译成功！
    echo.
    echo 运行说明：
    echo 1. 打开两个命令提示符窗口
    echo 2. 在第一个窗口运行：simple_demo.exe consumer
    echo 3. 在第二个窗口运行：simple_demo.exe producer
    echo.
    echo 注意：请先启动消费者，再启动生产者
) else (
    echo 编译失败！
)

pause
