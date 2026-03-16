#pragma once

#include <stdbool.h>
#include "Allocator.h"

typedef struct {
    void* data;
    u64 head, tail, capacity, chunksize;
} RingBuffer;

void _RingBuffer_Init(RingBuffer* rb, Allocator* alloc, u64 chunksize, u64 capacity);
void _RingBuffer_Deinit(RingBuffer* rb, Allocator* alloc);
bool _RingBuffer_Push(RingBuffer* rb, void* chunk);
bool _RingBuffer_Pop(RingBuffer* rb, void* chunk);
bool _RingBuffer_Empty(RingBuffer* rb);

#define RingBuffer_Init(T, rb, alloc, cap) _RingBuffer_Init(rb, alloc, sizeof(T), cap)
#define RingBuffer_Deinit(rb, alloc) _RingBuffer_Deinit(rb, alloc)
#define RingBuffer_Push(rb, chunk) _RingBuffer_Push(rb, (void*)(chunk))
#define RingBuffer_Pop(rb, chunk) _RingBuffer_Pop(rb, (void*)(chunk))
