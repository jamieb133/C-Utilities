#include <string.h>

#include <Allocator.h>
#include <Logger.h>
#include <RingBuffer.h>

void _RingBuffer_Init(RingBuffer* rb, Allocator* alloc, u64 chunksize, u64 capacity)
{
    Assert(rb, "Ringbuffer null");
    Assert(alloc, "Allocator null");
    Assert(chunksize > 0, "Chunksize is 0");
    Assert(capacity > 0, "Capacity is 0");

    rb->data = alloc->acquire(chunksize * capacity);
    rb->capacity = capacity + 1; // Extra space for implicit full/empty
    rb->chunksize = chunksize;
    rb->head = 0;
    rb->tail = 0;

    LogTrace("Created RingBuffer (chunksize=%u, capacity=%u)", rb->chunksize, rb->capacity);
}

void _RingBuffer_Deinit(RingBuffer* rb, Allocator* alloc)
{
    Assert(rb, "Ringbuffer null");
    Assert(alloc, "Allocator null");
    Assert(rb->data, "Ringbuffer data null");

    alloc->release(rb->data);
    rb->capacity = 0;
    rb->head = 0;
    rb->tail = 0;
}

bool _RingBuffer_Push(RingBuffer* rb, void* chunk)
{
    Assert(rb, "Ringbuffer null");
    Assert(chunk, "Chunk null");
    Assert(rb->data, "Data null");
    Assert(rb->chunksize > 0, "Chunksize is 0");

    if (((rb->head + 1) % rb->capacity) == rb->tail)
    {
        // Is full
        return false;
    }

    u64 index = rb->head * rb->chunksize;
    void* headptr = (u8*)rb->data + index;

    // Copy value into current head
    memcpy(headptr, chunk, rb->chunksize);

    // Move the head forward
    rb->head = (rb->head + 1) % rb->capacity;

    return true;
}

bool _RingBuffer_Pop(RingBuffer* rb, void* chunk)
{
    Assert(rb, "Ringbuffer null");
    Assert(chunk, "Chunk null");
    Assert(rb->data, "Data null");
    Assert(rb->chunksize > 0, "Chunksize is 0");

    if (rb->head == rb->tail)
    {
        // Is empty
        return false;
    }

    u64 index = rb->tail * rb->chunksize;
    void* tailptr = (u8*)rb->data + index;

    // Copy value from current tail
    memcpy(chunk, tailptr, rb->chunksize);

    // Move the tail forward
    rb->tail = (rb->tail + 1) % rb->capacity;

    return true;
}

bool _RingBuffer_Empty(RingBuffer *rb)
{
    Assert(rb, "Ringbuffer null");
    return (rb->head == rb->tail);
}
