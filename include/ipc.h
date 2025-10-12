#ifndef IPC_H
#define IPC_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// IPC 句柄（不透明）
typedef void* IPC_Handle;

// ========== 核心 API ==========

// 创建 IPC 通道
IPC_Handle ipc_create(size_t capacity);

// 发送数据（传递指针）
bool ipc_send(IPC_Handle handle, void *data);

// 接收数据（返回指针）
bool ipc_recv(IPC_Handle handle, void **data);

// 销毁 IPC 通道
void ipc_destroy(IPC_Handle handle);

// ========== 查询 API ==========

// 是否为空
bool ipc_is_empty(IPC_Handle handle);

// 是否已满
bool ipc_is_full(IPC_Handle handle);

// 获取当前数量
uint16_t ipc_count(IPC_Handle handle);

// ========== 信息 API ==========

// 获取实现类型
const char* ipc_get_type(void);

// 获取版本
const char* ipc_get_version(void);

#endif // IPC_H

