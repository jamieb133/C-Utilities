#pragma once

#ifdef __linux__
#include "posix/Thread.h"
#elif __APPLE__
#include "posix/Thread.h"
#elif _WIN32
#include "win32/Thread.h"
#else
#error "Thread.h not supported on this system"
#endif

/**
 * Thread
 */

void Thread_Create(Thread* thread, void* (*funcpt)(void*), void* args);
void Thread_Join(Thread* thread);

/**
 * Mutex
 */

void Mutex_Init(Mutex* mutex);
void Mutex_Deinit(Mutex* mutex);
void Mutex_Lock(Mutex* mutex);
void Mutex_Unlock(Mutex* mutex);

/**
 *  Condition Variable
 */

void CondVar_Init(CondVar* cv);
void CondVar_Deinit(CondVar* cv);
void CondVar_NotifyOne(CondVar* cv);
void CondVar_NotifyAll(CondVar* cv);
void CondVar_Wait(CondVar* cv, Mutex* mutex);

