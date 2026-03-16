#pragma once

#ifdef __linux__
#elif __APPLE__
#elif _WIN32
#else
#error "ConcurrentQueue not supported on this system"
#endif

#include "Thread.h"
#include "RingBuffer.h"

typedef struct {
    RingBuffer rb;
    Mutex mtx;
    CondVar cv;
} ConcurrentQueue;

void _ConcurrentQueue_Init(ConcurrentQueue* q, Allocator* alloc, u64 chunksize, u64 capacity);
void _ConcurrentQueue_Deinit(ConcurrentQueue* q, Allocator* alloc);
bool _ConcurrentQueue_Push(ConcurrentQueue* q, void* chunk);
bool _ConcurrentQueue_Pop(ConcurrentQueue* q, void* chunk);
void _ConcurrentQueue_Unblock(ConcurrentQueue* q);

#define ConcurrentQueue_Init(T, q, alloc, cap) _ConcurrentQueue_Init(q, alloc, sizeof(T), cap)
#define ConcurrentQueue_Deinit(q, alloc) _ConcurrentQueue_Deinit(q, alloc)
#define ConcurrentQueue_Push(q, chunk) _ConcurrentQueue_Push(q, (void*)(chunk))
#define ConcurrentQueue_Pop(q, chunk) _ConcurrentQueue_Pop(q, (void*)(chunk))
#define ConcurrentQueue_Unblock(q) _ConcurrentQueue_Unblock(q)

