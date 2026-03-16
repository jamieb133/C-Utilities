#include "ConcurrentQueue.h"
#include <Logger.h>
#include <ThreadPool.h>

static void* Worker(void* args)
{
    Assert(args, "args null");
    ThreadPool* tp = (ThreadPool*)args;

    LogTrace("Task worker started");

    while (atomic_load(&tp->running))
    {
        Task task;
        if (!ConcurrentQueue_Pop(&tp->taskQueue, &task))
        {
            LogTrace("No tasks popped");
            continue;
        }

        LogTrace("Executing task");
        task.cb(task.args);
        LogTrace("Task complete");
    }

    LogTrace("Task worker stopped");
    return NULL;
}

void ThreadPool_Init(ThreadPool* tp, Allocator* alloc, u16 numTasks, u8 numThreads)
{
    Assert(tp, "tp null");
    Assert(alloc, "alloc null");
    Assert(numTasks > 0, "numTasks zero");
    Assert(numThreads > 0, "numThreads zero");

    // Initialise
    ConcurrentQueue_Init(Task, &tp->taskQueue, alloc, numTasks);
    Array_Init(Thread, &tp->threads, alloc, numThreads);
    atomic_store(&tp->running, true);
    
    // Start thread pool
    for (u64 i = 0; i < numThreads; i++)
    {
        Thread* t = Array_Data(Thread, &tp->threads, i); 
        Thread_Create(t, Worker, (void*)tp);
    }
}

void ThreadPool_Deinit(ThreadPool* tp, Allocator* alloc)
{
    Assert(tp, "tp null");
    Assert(alloc, "alloc null");

    // Stop thread pool
    atomic_store(&tp->running, false);
    ConcurrentQueue_Unblock(&tp->taskQueue);
    for (u64 i = 0; i < tp->threads.capacity; i++)
    {
        Thread* t = Array_Data(Thread, &tp->threads, i); 
        Thread_Join(t);
    }

    // Cleanup
    ConcurrentQueue_Deinit(&tp->taskQueue, alloc);
    Array_Deinit(&tp->threads, alloc);
}

void ThreadPool_Push(ThreadPool* tp, void (*cb)(void*), void* args)
{
    Assert(tp, "tp null");
    Assert(cb, "cb null");

    Task task = (Task) { .cb = cb, .args = args };
    bool res = ConcurrentQueue_Push(&tp->taskQueue, &task);
    Assert(res, "failed to push task");
}
