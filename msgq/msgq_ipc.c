#include "../include/ipc.h"
#include "queue.h"

IPC_Handle ipc_create(size_t capacity) {
    return (IPC_Handle)queue_create((uint16_t)capacity);
}

bool ipc_send(IPC_Handle handle, void *data) {
    return queue_enqueue((Queue*)handle, data);
}

bool ipc_recv(IPC_Handle handle, void **data) {
    return queue_dequeue((Queue*)handle, data);
}

void ipc_destroy(IPC_Handle handle) {
    queue_destroy((Queue*)handle);
}

bool ipc_is_empty(IPC_Handle handle) {
    return queue_is_empty((Queue*)handle);
}

bool ipc_is_full(IPC_Handle handle) {
    return queue_is_full((Queue*)handle);
}

uint16_t ipc_count(IPC_Handle handle) {
    return queue_get_count((Queue*)handle);
}

const char* ipc_get_type(void) {
    return "MessageQueue";
}

const char* ipc_get_version(void) {
    return queue_get_version();
}

