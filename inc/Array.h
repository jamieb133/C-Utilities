#pragma once

#include "Allocator.h"
#include "CustomTypes.h"

typedef struct {
    void* data;
    u64 capacity;
    u64 chunksize;
} Array;

void _Array_Init(Array* arr, Allocator* alloc, u64 chunksize, u64 capacity);
void _Array_Deinit(Array* arr, Allocator* alloc);
void _Array_Get(Array* arr, void* data, u64 index);
void _Array_Set(Array* arr, void* data, u64 index);
void* _Array_Data(Array* arr, u64 index);

#define Array_Init(T, arr, alloc, capacity) _Array_Init(arr, alloc, sizeof(T), capacity)
#define Array_Deinit(arr, alloc) _Array_Deinit(arr, alloc)
#define Array_Get(arr, data, index) _Array_Get(arr, (void*)data, index)
#define Array_Set(arr, data, index) _Array_Set(arr, (void*)data, index)
#define Array_Data(T, arr, index) (T*)_Array_Data(arr, index)

