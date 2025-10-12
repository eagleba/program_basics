#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "ipc.h"

#define MAX_FILENAME 256
#define MAX_FILE_SIZE (64 * 1024)  // 64KB 小文件

// ===== 消息定义 =====
typedef struct {
    char filename[MAX_FILENAME];
} Request;

typedef struct {
    int status;          // 0: 成功, -1: 失败
    size_t size;         // 文件大小
    char data[MAX_FILE_SIZE];
} Response;

// ===== 服务器 API =====
static struct {
    IPC_Handle my_queue;
    IPC_Handle peer_queue;
} server_ctx = {NULL, NULL};

IPC_Handle server_init(void) {
    server_ctx.my_queue = ipc_create(10);
    printf("[Server API] Created receive queue\n");
    return server_ctx.my_queue;
}

void server_set_client_queue(IPC_Handle q) {
    server_ctx.peer_queue = q;
    printf("[Server API] Set client queue\n");
}

bool server_recv_request(Request **req) {
    return ipc_recv(server_ctx.my_queue, (void**)req);
}

bool server_send_response(Response *resp) {
    return ipc_send(server_ctx.peer_queue, resp);
}

void server_cleanup(void) {
    if (server_ctx.my_queue) {
        ipc_destroy(server_ctx.my_queue);
        printf("[Server API] Cleaned up\n");
    }
}

// ===== 客户端 API =====
static struct {
    IPC_Handle my_queue;
    IPC_Handle peer_queue;
} client_ctx = {NULL, NULL};

IPC_Handle client_init(void) {
    client_ctx.my_queue = ipc_create(10);
    printf("[Client API] Created receive queue\n");
    return client_ctx.my_queue;
}

void client_set_server_queue(IPC_Handle q) {
    client_ctx.peer_queue = q;
    printf("[Client API] Set server queue\n");
}

bool client_send_request(Request *req) {
    return ipc_send(client_ctx.peer_queue, req);
}

bool client_recv_response(Response **resp) {
    return ipc_recv(client_ctx.my_queue, (void**)resp);
}

void client_cleanup(void) {
    if (client_ctx.my_queue) {
        ipc_destroy(client_ctx.my_queue);
        printf("[Client API] Cleaned up\n");
    }
}

// ===== 服务器线程 =====
void* server_thread(void* arg) {
    (void)arg;
    
    printf("[Server] Started, waiting for request...\n");
    
    Request *req;
    // 循环等待请求
    while (!server_recv_request(&req)) {
        usleep(10000);  // 10ms
    }
    
    if (req) {
        printf("[Server] Received request for file: %s\n", req->filename);
        
        // 读取文件
        FILE *fp = fopen(req->filename, "rb");
        Response *resp = malloc(sizeof(Response));
        
        if (fp == NULL) {
            printf("[Server] Error: Cannot open file '%s'\n", req->filename);
            resp->status = -1;
            resp->size = 0;
            snprintf(resp->data, sizeof(resp->data), 
                    "Error: Cannot open file '%s'", req->filename);
        } else {
            // 读取文件内容
            resp->size = fread(resp->data, 1, MAX_FILE_SIZE, fp);
            resp->status = 0;
            fclose(fp);
            printf("[Server] Read %zu bytes from file\n", resp->size);
        }
        
        // 发送响应
        server_send_response(resp);
        printf("[Server] Response sent\n");
        
        free(req);
    }
    
    printf("[Server] Thread exiting\n");
    return NULL;
}

// ===== 客户端线程 =====
void* client_thread(void* arg) {
    (void)arg;
    
    printf("[Client] Started\n");
    
    // 获取用户输入
    char filename[MAX_FILENAME];
    printf("[Client] Enter filename: ");
    fflush(stdout);
    if (fgets(filename, sizeof(filename), stdin) == NULL) {
        return NULL;
    }
    filename[strcspn(filename, "\n")] = 0;
    
    // 发送请求
    Request *req = malloc(sizeof(Request));
    strncpy(req->filename, filename, sizeof(req->filename) - 1);
    req->filename[sizeof(req->filename) - 1] = '\0';
    
    printf("[Client] Requesting file: %s\n", filename);
    client_send_request(req);
    
    // 接收响应 - 循环等待
    Response *resp;
    printf("[Client] Waiting for response...\n");
    while (!client_recv_response(&resp)) {
        usleep(10000);  // 10ms
    }
    
    if (resp) {
        if (resp->status == 0) {
            printf("\n========== File Content ==========\n");
            fwrite(resp->data, 1, resp->size, stdout);
            printf("\n========== End (Total: %zu bytes) ==========\n", resp->size);
        } else {
            printf("[Client] %s\n", resp->data);
        }
        free(resp);
    }
    
    printf("[Client] Thread exiting\n");
    return NULL;
}

// ===== Main =====
int main() {
    printf("============================================\n");
    printf("  File Server - Client/Server Test\n");
    printf("  IPC Type: %s\n", ipc_get_type());
    printf("  Version: %s\n", ipc_get_version());
    printf("============================================\n\n");
    
    // 1. 初始化
    IPC_Handle server_q = server_init();
    IPC_Handle client_q = client_init();
    
    if (!server_q || !client_q) {
        printf("Error: Failed to initialize IPC\n");
        return -1;
    }
    
    // 2. 交换队列句柄
    server_set_client_queue(client_q);
    client_set_server_queue(server_q);
    
    printf("\n");
    
    // 3. 启动线程
    pthread_t server, client;
    pthread_create(&server, NULL, server_thread, NULL);
    sleep(1);  // 等待服务器准备好
    pthread_create(&client, NULL, client_thread, NULL);
    
    // 4. 等待完成
    pthread_join(client, NULL);
    pthread_join(server, NULL);
    
    printf("\n");
    
    // 5. 清理
    server_cleanup();
    client_cleanup();
    
    printf("\n============================================\n");
    printf("  Test Complete\n");
    printf("============================================\n");
    
    return 0;
}
