#include "Allocator.h"
#include <TestFramework.h>
#include <Array.h>

static Allocator alloc;

TEST(ArrayTest, Array)
{
    Array arr;

    CHECK_DEATH(Array_Init(int, NULL, &alloc, 10));
    CHECK_DEATH(Array_Init(int, &arr, NULL, 10));
    CHECK_DEATH(Array_Init(int, &arr, &alloc, 0));
    
    Array_Init(int, &arr, &alloc, 10);

    int v = 100;
    CHECK_DEATH(Array_Set(NULL, &v, 0));
    CHECK_DEATH(Array_Set(&arr, NULL, 0));
    CHECK_DEATH(Array_Set(&arr, &v, 11)); // Out of bounds

    for (int i = 0; i < 10; i++)
    {
        Array_Set(&arr, &i, i);
    }

    CHECK_DEATH(Array_Get(NULL, &v, 0));
    CHECK_DEATH(Array_Get(&arr, NULL, 0));
    CHECK_DEATH(Array_Get(&arr, &v, 11)); // Out of bounds
    
    for (int i = 0; i < 10; i++)
    {
        Array_Get(&arr, &v, i);
        CHECK_TRUE(v == i);
    }

    CHECK_DEATH(Array_Deinit(NULL, &alloc));
    CHECK_DEATH(Array_Deinit(&arr, NULL));
    Array_Deinit(&arr, &alloc);
}

TEST_SETUP(ArrayTest)
{
    ADD_TEST(ArrayTest, Array); 
}

TEST_BRINGUP(ArrayTest) { DefaultAllocator_Create(&alloc); }
TEST_TEARDOWN(ArrayTest) {}

