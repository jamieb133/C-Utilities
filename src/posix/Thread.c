#define _GNU_SOURCE
#include <sched.h>

#include <Logger.h>
#include <Thread.h>
#include <pthread.h>

/**
 * Thread
 */

void Thread_Create(Thread* thread, void* (*funcptr)(void*), void* args)
{
    Assert(thread, "thread null");
    Assert(funcptr, "funcptr null");
    pthread_create(&thread->pthread_, NULL, funcptr, args);
}

void Thread_Join(Thread* thread)
{
    Assert(thread, "thread null");
    pthread_join(thread->pthread_, NULL);
}

u64 Thread_Id(void)
{
    return (u64)pthread_self();
}

u8 Thread_CoreId(void)
{
    return (u8)sched_getcpu();
}

/**
 * Mutex 
 */

void Mutex_Init(Mutex* mutex)
{
    Assert(mutex, "mutex null");
    pthread_mutex_init(&mutex->mtx, NULL);
}

void Mutex_Deinit(Mutex* mutex)
{
    Assert(mutex, "mutex null");
    pthread_mutex_destroy(&mutex->mtx);
}

void Mutex_Lock(Mutex* mutex)
{
    Assert(mutex, "mutex null");
    pthread_mutex_lock(&mutex->mtx); 
}

void Mutex_Unlock(Mutex* mutex)
{
    Assert(mutex, "mutex null");
    pthread_mutex_unlock(&mutex->mtx); 
}

/**
 * Mutex 
 */

void CondVar_Init(CondVar* cv)
{
    Assert(cv, "cv null");
    pthread_cond_init(&cv->cv, NULL);
}

void CondVar_Deinit(CondVar* cv)
{
    Assert(cv, "cv null");
    pthread_cond_destroy(&cv->cv);
}

void CondVar_NotifyOne(CondVar* cv)
{
    Assert(cv, "cv null");
    pthread_cond_signal(&cv->cv);
}

void CondVar_NotifyAll(CondVar* cv)
{
    Assert(cv, "cv null");
    pthread_cond_broadcast(&cv->cv);
}

void CondVar_Wait(CondVar* cv, Mutex* mutex)
{
    Assert(cv, "cv null");
    Assert(mutex, "mutex null");
    pthread_cond_wait(&cv->cv, &mutex->mtx);
}
