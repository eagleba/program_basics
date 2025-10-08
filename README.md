# Cursor环境编译和调试指南

## 🚀 快速开始

### 1. 环境检查
确保你的系统已安装：
- **MinGW-w64** 或 **MSYS2**（提供gcc编译器）
- **Cursor编辑器**

### 2. 一键编译
在Cursor中打开终端（Ctrl+`），运行：
```bash
cursor_build.bat
```

## 🔧 编译方式

### 方式1：使用Cursor任务（推荐）
1. 按 `Ctrl+Shift+P` 打开命令面板
2. 输入 "Tasks: Run Task"
3. 选择以下任务之一：
   - **编译简单队列演示** - 编译基础队列示例
   - **编译简化Windows演示** - 编译消息队列演示
   - **清理编译文件** - 删除所有编译生成的文件

### 方式2：使用快捷键
- `Ctrl+Shift+B` - 运行默认构建任务（编译简单队列演示）

### 方式3：手动编译
在终端中运行：
```bash
# 编译简单队列演示
gcc -Wall -Wextra -std=c99 -g -O2 -o msgq/examples/02-principles/queue_demo.exe msgq/examples/02-principles/simple_queue.c msgq/examples/02-principles/queue_demo.c

# 编译简化Windows演示
gcc -Wall -Wextra -std=c99 -g -O2 -o msgq/examples/03-practice/sensor_demo/simple_demo.exe msgq/examples/03-practice/sensor_demo/simple_windows_demo.c
```

## 🐛 调试方式

### 方式1：使用Cursor调试器（推荐）
1. 按 `F5` 开始调试
2. 选择调试配置：
   - **调试简单队列演示** - 调试基础队列
   - **调试简化演示-消费者** - 调试消费者程序
   - **调试简化演示-生产者** - 调试生产者程序

### 方式2：设置断点
1. 在代码行号左侧点击设置断点（红点）
2. 按 `F5` 开始调试
3. 程序会在断点处暂停

### 方式3：调试控制
- `F5` - 继续执行
- `F10` - 单步执行（跳过函数）
- `F11` - 单步执行（进入函数）
- `Shift+F11` - 跳出函数
- `Ctrl+Shift+F5` - 重启调试

## 📁 项目结构

```
msgq/
├── examples/
│   ├── 02-principles/           # 基础队列实现
│   │   ├── simple_queue.h/c     # 队列实现
│   │   ├── queue_demo.c         # 演示程序
│   │   └── queue_demo.exe       # 编译后的可执行文件
│   └── 03-practice/
│       └── sensor_demo/         # 消息队列演示
│           ├── simple_windows_demo.c
│           └── simple_demo.exe  # 编译后的可执行文件
└── .vscode/                     # Cursor配置文件
    ├── tasks.json              # 编译任务配置
    ├── launch.json             # 调试配置
    └── c_cpp_properties.json   # C/C++属性配置
```

## 🎯 运行演示

### 简单队列演示
```bash
# 直接运行
msgq\examples\02-principles\queue_demo.exe
```

### 消息队列演示（需要两个终端）
**终端1（消费者）：**
```bash
msgq\examples\03-practice\sensor_demo\simple_demo.exe consumer
```

**终端2（生产者）：**
```bash
msgq\examples\03-practice\sensor_demo\simple_demo.exe producer
```

## 🔍 调试技巧

### 1. 查看变量值
- 鼠标悬停在变量上查看值
- 在"变量"面板中查看所有变量
- 在"监视"面板中添加表达式

### 2. 查看调用栈
- 在"调用栈"面板中查看函数调用链
- 点击不同层级查看对应的变量状态

### 3. 查看内存
- 在"监视"面板中添加 `&变量名` 查看地址
- 使用 `*地址` 查看内存内容

### 4. 条件断点
- 右键断点 → 编辑断点
- 添加条件表达式，只有条件为真时才暂停

## ⚠️ 常见问题

### 1. "gcc不是内部或外部命令"
**解决方案：**
- 安装MinGW-w64或MSYS2
- 将gcc路径添加到系统PATH环境变量

### 2. 调试器无法启动
**解决方案：**
- 确保已安装gdb调试器
- 检查launch.json配置是否正确

### 3. 编译错误
**解决方案：**
- 检查代码语法
- 确保所有头文件路径正确
- 查看"问题"面板中的错误信息

### 4. 程序运行异常
**解决方案：**
- 使用调试器逐步执行
- 检查变量值是否正确
- 查看控制台输出

## 🎨 推荐设置

### 1. 安装扩展
- **C/C++** - Microsoft官方C/C++扩展
- **Code Runner** - 快速运行代码
- **Better Comments** - 更好的注释显示

### 2. 配置设置
在设置中启用：
- 自动保存
- 代码格式化
- 智能提示

### 3. 快捷键自定义
- `Ctrl+F5` - 运行而不调试
- `Ctrl+Shift+F5` - 重启调试
- `F9` - 切换断点

## 📚 学习建议

1. **从简单开始** - 先运行简单队列演示，理解基本概念
2. **逐步调试** - 使用调试器观察程序执行过程
3. **修改代码** - 尝试修改参数，观察不同效果
4. **添加日志** - 在关键位置添加printf输出
5. **实验扩展** - 基于现有代码添加新功能

现在你可以在Cursor中愉快地编译和调试C程序了！🎉
