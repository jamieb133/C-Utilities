#include "RingBuffer.h"
#include "Thread.h"
#include <ConcurrentQueue.h>
#include <Logger.h>

void _ConcurrentQueue_Init(ConcurrentQueue* q, Allocator* alloc, u64 chunksize, u64 capacity)
{
    Assert(q, "q null");
    Assert(alloc, "alloc null");
    Assert(chunksize > 0, "chunksize zero");
    Assert(capacity > 0, "capacity zero");

    _RingBuffer_Init(&q->rb, alloc, chunksize, capacity);
    Mutex_Init(&q->mtx);
    CondVar_Init(&q->cv);
}

void _ConcurrentQueue_Deinit(ConcurrentQueue* q, Allocator* alloc)
{
    Assert(q, "q null");
    Assert(alloc, "alloc null");

    _RingBuffer_Deinit(&q->rb, alloc);
    Mutex_Deinit(&q->mtx);
    CondVar_Deinit(&q->cv);
}

bool _ConcurrentQueue_Push(ConcurrentQueue* q, void* chunk)
{
    Assert(q, "q null");
    Assert(chunk, "chunk null");

    Mutex_Lock(&q->mtx);
    bool result = _RingBuffer_Push(&q->rb, chunk);
    Mutex_Unlock(&q->mtx);
    CondVar_NotifyOne(&q->cv);

    return result;
}

bool _ConcurrentQueue_Pop(ConcurrentQueue* q, void* chunk)
{
    Assert(q, "q null");
    Assert(chunk, "chunk null");

    Mutex_Lock(&q->mtx);

    if (_RingBuffer_Empty(&q->rb))
    {
        CondVar_Wait(&q->cv, &q->mtx);
    }

    bool result = _RingBuffer_Pop(&q->rb, chunk);
    Mutex_Unlock(&q->mtx);

    return result;
}

void _ConcurrentQueue_Unblock(ConcurrentQueue *q)
{
    Assert(q, "q null");
    Mutex_Lock(&q->mtx);
    CondVar_NotifyAll(&q->cv);
    Mutex_Unlock(&q->mtx);
}

