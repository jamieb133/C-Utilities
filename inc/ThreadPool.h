#pragma once

#ifdef __linux__
#include "posix/ThreadPool.h"
#elif __APPLE__
#include "posix/ThreadPool.h"
#elif _WIN32
#include "win32/ThreadPool.h"
#else
#error "ThreadPool.h not supported on this system"
#endif

#include "CustomTypes.h"
#include "Allocator.h"

void ThreadPool_Init(ThreadPool* tp, Allocator* alloc, u16 numTasks, u8 numThreads);
void ThreadPool_Deinit(ThreadPool* tp, Allocator* alloc);
void ThreadPool_Push(ThreadPool* tp, void (*cb)(void*), void* args);

