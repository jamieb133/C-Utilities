#pragma once

#include <Array.h>
#include <ConcurrentQueue.h>
#include <CustomTypes.h>
#include <Thread.h>

typedef struct {
    void (*cb)(void*);
    void* args;
} Task;

typedef struct {
    ConcurrentQueue taskQueue;
    Array threads;
    atomic_bool running;
} ThreadPool;

