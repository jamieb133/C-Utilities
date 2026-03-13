#pragma once

#include <stdlib.h>
#include "CustomTypes.h"
#include "Logger.h"

typedef struct {
    void* (*acquire)(u64);
    void (*release)(void*);
} Allocator;

#define Acquire(alloc, T, size) \
    ((T*)alloc->acquire(size * sizeof(T))

#define Release(alloc, ptr) \
    alloc->release((void*)ptr); \
    ptr = NULL

void* DefaultAllocator_Acquire(u64 size) ;
void DefaultAllocator_Release(void* ptr);
void DefaultAllocator_Create(Allocator* alloc);

