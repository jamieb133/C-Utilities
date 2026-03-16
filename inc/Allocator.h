#pragma once

#include <stdbool.h>
#include "CustomTypes.h"

void _Memcpy(void* dst, void* src, u64 size);
#define Memcpy(T, dst, src, num) _Memcpy((void*)dst, (void*)src, sizeof(T) * num)

bool _Memcmp(void* dst, void* src, u64 size);
#define Memcmp(T, dst, src, num) _Memcmp((void*)dst, (void*)src, sizeof(T) * num)

typedef struct {
    void* (*acquire)(u64);
    void (*release)(void*);
} Allocator;

#define Acquire(alloc, T, size) \
    ((T*)alloc->acquire(size * sizeof(T)))

#define Release(alloc, ptr) \
    alloc->release((void*)ptr);

void* DefaultAllocator_Acquire(u64 size) ;
void DefaultAllocator_Release(void* ptr);
void DefaultAllocator_Create(Allocator* alloc);

