#include <Allocator.h>

void* DefaultAllocator_Acquire(u64 size) 
{ 
    void* ptr = malloc(size); 
    Assert(ptr != NULL, "malloc failed");
    return ptr;
}

void DefaultAllocator_Release(void* ptr)
{
    Assert(ptr != NULL, "Pointer null on release");
    free(ptr);
}

void DefaultAllocator_Create(Allocator* alloc) 
{ 
    alloc->acquire = DefaultAllocator_Acquire;
    alloc->release = DefaultAllocator_Release;
}

