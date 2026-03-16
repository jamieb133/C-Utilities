#include <unistd.h>
#include <TestFramework.h>
#include <ConcurrentQueue.h>

static Allocator alloc;

int values[10];
int count = 0;
atomic_bool running;

void* thread(void* args)
{
    Assert(args, "args null");
    ConcurrentQueue* q = (ConcurrentQueue*)args;
    int val;

    LogTrace("started thread");

    while (atomic_load(&running))
    {
        if (ConcurrentQueue_Pop(q, &val))
        {
            LogTrace("popped %d", count);
            values[count] = val;
            count++;
        }
    }

    LogTrace("thread finished");

    return NULL;
}

TEST(ConcurrentQueueTest, InitDeinit)
{
    ConcurrentQueue q;

    CHECK_DEATH(ConcurrentQueue_Init(int, NULL, &alloc, 10));
    CHECK_DEATH(ConcurrentQueue_Init(int, &q, NULL, 10));
    CHECK_DEATH(ConcurrentQueue_Init(int, &q, &alloc, 0));
    ConcurrentQueue_Init(int, &q, &alloc, 10);

    CHECK_DEATH(ConcurrentQueue_Deinit(NULL, &alloc));
    CHECK_DEATH(ConcurrentQueue_Deinit(&q, NULL));
    ConcurrentQueue_Deinit(&q, &alloc);
}

TEST(ConcurrentQueueTest, PushPop)
{
    ConcurrentQueue q;

    ConcurrentQueue_Init(int, &q, &alloc, 10);

    int v = 10;
    CHECK_DEATH(ConcurrentQueue_Push(NULL, &v));
    CHECK_DEATH(ConcurrentQueue_Push(&q, NULL));

    atomic_store(&running, true);
    Thread t;
    Thread_Create(&t, thread, (void*)&q);

    for (int i = 0; i < 10; i++)
    {
        ConcurrentQueue_Push(&q, &i);
    }

    CHECK_FALSE(ConcurrentQueue_Push(&q, &v));

    usleep(250000);
    atomic_store(&running, false);
    ConcurrentQueue_Unblock(&q);
    Thread_Join(&t);
    
    LogTrace("thread joined");

    for (int i = 0; i < 10; i++)
    {
        CHECK_TRUE(values[i] == i);
    }

    ConcurrentQueue_Deinit(&q, &alloc);
}

TEST_SETUP(ConcurrentQueueTest)
{
    ADD_TEST(ConcurrentQueueTest, InitDeinit);
    ADD_TEST(ConcurrentQueueTest, PushPop);
}

TEST_BRINGUP(ConcurrentQueueTest) { DefaultAllocator_Create(&alloc); }
TEST_TEARDOWN(ConcurrentQueueTest) {}
