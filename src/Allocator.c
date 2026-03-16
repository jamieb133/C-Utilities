#include <Allocator.h>
#include <Logger.h>
#include <stdlib.h>

void _Memcpy(void* dst, void* src, u64 size)
{
    // TODO optimise this

    u8* dstptr = (u8*)dst;
    u8* srcptr = (u8*)src;

    for (u64 i = 0; i < size; i++)
    {
        dstptr[i] = srcptr[i];  
    }
}

bool _Memcmp(void* dst, void* src, u64 size)
{
    // TODO optimise this

    u8* dstptr = (u8*)dst;
    u8* srcptr = (u8*)src;

    for (u64 i = 0; i < size; i++)
    {
        if (dstptr[i] != srcptr[i])
        {
            return false;
        }
    }

    return true;
}

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

