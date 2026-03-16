#include <unistd.h>
#include <TestFramework.h>
#include <Thread.h>
#include <ThreadPool.h>

static Allocator alloc;
static u64 threadIds[10] = { 0, };

typedef struct {
    Mutex mtx;
    CondVar cv;
    int count;
} TaskArgs;

void Callback(void* args)
{
    Assert(args, "args null");
    TaskArgs* targs = (TaskArgs*)args;
    usleep((targs->count + 1) * 100000);
    Mutex_Lock(&targs->mtx);
    LogInfo("task %d running", targs->count);
    threadIds[targs->count] = Thread_Id();
    targs->count++;
    Mutex_Unlock(&targs->mtx);
    CondVar_NotifyAll(&targs->cv);
}

int Compare(const void* a, const void* b)
{
    u64 val_a = *(u64*)a;
    u64 val_b = *(u64*)b;
    
    if (val_a < val_b) 
        return -1;
    if (val_a > val_b) 
        return 1;

    return 0;
}

TEST(ThreadPoolTest, ThreadPool)
{
    ThreadPool tp;

    // Initialise targs
    TaskArgs targs;
    targs.count = 0;
    Mutex_Init(&targs.mtx);
    CondVar_Init(&targs.cv);

    // Init
    CHECK_DEATH(ThreadPool_Init(NULL, &alloc, 10, 4));
    CHECK_DEATH(ThreadPool_Init(&tp, &alloc, 0, 4));
    CHECK_DEATH(ThreadPool_Init(&tp, &alloc, 10, 0));
    ThreadPool_Init(&tp, &alloc, 10, 4);

    // Push
    CHECK_DEATH(ThreadPool_Push(NULL, Callback, &targs));
    CHECK_DEATH(ThreadPool_Push(&tp, NULL, &targs));

    for (int i = 0; i < 10; i++)
    {
        LogInfo("push task %d", i);
        ThreadPool_Push(&tp, Callback, &targs);
    }

    int count = 0;
    for (;;)
    {
        LogInfo("Wait for task %d", count);
        CondVar_Wait(&targs.cv, &targs.mtx);
        if (targs.count >= 10)
        {
            Mutex_Unlock(&targs.mtx);
            LogInfo("Finished waiting on tasks");
            break;
        }

        count++;
    }

    // Catch any extraneous tasks
    usleep(250);
    Mutex_Lock(&targs.mtx);
    CHECK_TRUE(targs.count == 10);
    Mutex_Unlock(&targs.mtx);

    // Check that 4 threads were running
    u64 copy[10];
    Memcpy(u64, copy, threadIds, 10);
    qsort(copy, 10, sizeof(u64), Compare);
    u64 unique = 1;
    for (int i = 1; i < 10; i++)
    {
        if (copy[i] != copy[i - 1])
            unique++;
    }
    CHECK_TRUE(unique == 4);

    // Deinit
    CHECK_DEATH(ThreadPool_Deinit(NULL, &alloc));
    CHECK_DEATH(ThreadPool_Deinit(&tp, NULL));
    ThreadPool_Deinit(&tp, &alloc);

    // Cleanup
    Mutex_Deinit(&targs.mtx);
    CondVar_Deinit(&targs.cv);
}

TEST_SETUP(ThreadPoolTest)
{
    ADD_TEST(ThreadPoolTest, ThreadPool); 
}

TEST_BRINGUP(ThreadPoolTest) 
{
    DefaultAllocator_Create(&alloc);
}

TEST_TEARDOWN(ThreadPoolTest) {}

