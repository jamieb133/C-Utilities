#pragma once

#include <pthread.h>

typedef struct {
    pthread_t pthread_;
} Thread;

typedef struct {
    pthread_mutex_t mtx;
} Mutex;

typedef struct {
    pthread_cond_t cv;
} CondVar;

