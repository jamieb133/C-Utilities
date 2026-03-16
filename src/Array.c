#include <Allocator.h>
#include <Array.h>
#include <Logger.h>

void _Array_Init(Array* arr, Allocator* alloc, u64 chunksize, u64 capacity)
{
    Assert(arr, "arr null");
    Assert(alloc, "alloc null");
    Assert(chunksize > 0, "chunksize zero");
    Assert(capacity > 0, "capacity zero");

    arr->data = alloc->acquire(chunksize * capacity);
    arr->capacity = capacity;
    arr->chunksize = chunksize;
}

void _Array_Deinit(Array* arr, Allocator* alloc)
{
    Assert(arr, "arr null");
    Assert(alloc, "alloc null");
    
    alloc->release(arr->data);
    arr->capacity = 0;
    arr->chunksize = 0;
}

void _Array_Get(Array* arr, void* data, u64 index)
{
    Assert(arr, "arr null");
    Assert(data, "data null");
    Assert(index < arr->capacity, "index out of bounds");
    _Memcpy(data, &arr->data[index * arr->chunksize], arr->chunksize);
}

void _Array_Set(Array* arr, void* data, u64 index)
{
    Assert(arr, "arr null");
    Assert(data, "data null");
    Assert(index < arr->capacity, "index out of bounds");
    _Memcpy(&arr->data[index * arr->chunksize], data, arr->chunksize);
}

void* _Array_Data(Array* arr, u64 index)
{
    Assert(arr, "arr null");
    Assert(index < arr->capacity, "index out of bounds");
    return &arr->data[index * arr->chunksize];
}

