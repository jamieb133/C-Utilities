#include <TestFramework.h>
#include <Thread.h>
#include <String.h>

typedef struct{
    const char* name;
} ThreadArgs;

static ThreadArgs currentArgs_;
static Mutex mutex_;
static CondVar cv_;

static void* Callback(void* args)
{
    Assert(args != NULL, "ThreadArgs null");
    currentArgs_ = *((ThreadArgs*)args);
    LogInfo("Callback args: name is %s", currentArgs_.name);
    CondVar_NotifyAll(&cv_);
    return NULL;
}

TEST(ThreadTest, Mutex)
{
    Mutex mutex;
    
    // Init
    Mutex_Init(&mutex);
    CHECK_DEATH(Mutex_Init(NULL));

    // Lock
    Mutex_Lock(&mutex);
    CHECK_DEATH(Mutex_Lock(NULL));

    // Unlock
    Mutex_Unlock(&mutex);
    CHECK_DEATH(Mutex_Unlock(NULL));

    // Deinit
    Mutex_Deinit(&mutex);
    CHECK_DEATH(Mutex_Deinit(NULL));
}

TEST(ThreadTest, CondVar)
{
    CondVar cv;
    Mutex mutex;

    // Init
    CondVar_Init(&cv);
    CHECK_DEATH(CondVar_Init(NULL));

    // NotifyOne
    CondVar_NotifyOne(&cv);
    CHECK_DEATH(CondVar_NotifyOne(NULL));

    // NotifyAll
    CondVar_NotifyAll(&cv);
    CHECK_DEATH(CondVar_NotifyAll(NULL));

    // Deinit
    CondVar_Deinit(&cv);
    CHECK_DEATH(CondVar_Deinit(NULL));

    // Wait (can't test valid call without a real thread, implicitly tested in the thread test)
    CHECK_DEATH(CondVar_Wait(NULL, &mutex));
    CHECK_DEATH(CondVar_Wait(&cv, NULL));
}

TEST(ThreadTest, Thread)
{
    Thread t;
    ThreadArgs targs = (ThreadArgs) { .name = "hello" };

    // Null checks
    CHECK_DEATH(Thread_Create(NULL, Callback, NULL));
    CHECK_DEATH(Thread_Create(&t, NULL, NULL));
    CHECK_DEATH(Thread_Join(NULL));

    // Create
    Mutex_Init(&mutex_);
    CondVar_Init(&cv_);
    Thread_Create(&t, Callback, &targs);

    // Wait for thread
    CondVar_Wait(&cv_, &mutex_);
    CHECK_TRUE(Strcmp(currentArgs_.name, targs.name));

    // Clean up
    Thread_Join(&t);
    Mutex_Deinit(&mutex_);
    CondVar_Deinit(&cv_);
}

TEST_SETUP(ThreadTest)
{
    ADD_TEST(ThreadTest, Mutex); 
    ADD_TEST(ThreadTest, CondVar); 
    ADD_TEST(ThreadTest, Thread); 
}

TEST_BRINGUP(ThreadTest) {}
TEST_TEARDOWN(ThreadTest) {}

