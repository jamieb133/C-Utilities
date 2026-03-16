#pragma once

#include <stdbool.h>
#include <pthread.h>

typedef struct {
    pthread_t pthread_;
} Thread;

void Thread_Create(Thread* thread, void* (*funcpt)(void*), void* args);
void Thread_Join(Thread* thread);

typedef struct {
    pthread_mutex_t mtx;
} Mutex;

void Mutex_Init(Mutex* mutex);
void Mutex_Deinit(Mutex* mutex);
void Mutex_Lock(Mutex* mutex);
void Mutex_Unlock(Mutex* mutex);

typedef struct {
    pthread_cond_t cv;
} CondVar;

void CondVar_Init(CondVar* cv);
void CondVar_Deinit(CondVar* cv);
void CondVar_NotifyOne(CondVar* cv);
void CondVar_NotifyAll(CondVar* cv);
void CondVar_Wait(CondVar* cv, Mutex* mutex);

