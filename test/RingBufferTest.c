#include <TestFramework.h>
#include <RingBuffer.h>

static Allocator alloc;

typedef struct {
    char str[1024];
} BigString;

TEST(RingBuffer, InitDeinit)
{
    RingBuffer rb;

    // Null ring buffer
    CHECK_DEATH(RingBuffer_Init(int, NULL, &alloc, 10));
    // Null allocator
    CHECK_DEATH(RingBuffer_Init(int, &rb, NULL, 10));
    // Zero capacity 
    CHECK_DEATH(RingBuffer_Init(int, &rb, &alloc, 0));

    // Valid init
    RingBuffer_Init(int, &rb, &alloc, 10);

    // Valid deinit
    RingBuffer_Deinit(&rb, &alloc);
}

TEST(RingBuffer, PushPop)
{
    int value;
    RingBuffer rb;
    RingBuffer_Init(int, &rb, &alloc, 10);

    // Null rb
    CHECK_DEATH(RingBuffer_Push(NULL, &value)); 
    // Null value
    CHECK_DEATH(RingBuffer_Push(&rb, NULL));

    // Queue empty
    CHECK_FALSE(RingBuffer_Pop(&rb, &value));

    // Valid pushes
    for (value = 0; value < 10; value++)
    {
        CHECK_TRUE(RingBuffer_Push(&rb, &value));
    }

    // Queue full
    CHECK_FALSE(RingBuffer_Push(&rb, &value));

    // Pop values
    for (int i = 0; i < 10; i++)
    {
        CHECK_TRUE(RingBuffer_Pop(&rb, &value));
        CHECK_TRUE(value == i);
    }

    RingBuffer_Deinit(&rb, &alloc);
}

TEST_SETUP(RingBuffer)
{
    DefaultAllocator_Create(&alloc);
    ADD_TEST(RingBuffer, InitDeinit);
    ADD_TEST(RingBuffer, PushPop);
}

TEST_BRINGUP(RingBuffer){}
TEST_TEARDOWN(RingBuffer){}
