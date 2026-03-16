#include "Allocator.h"
#include <TestFramework.h>
#include <String.h>

static Allocator alloc;

TEST(StringTest, InitDeinit)
{
    String str;

    CHECK_DEATH(String_Init(NULL, &alloc, "hello"));
    CHECK_DEATH(String_Init(&str, NULL, "hello"));
    CHECK_DEATH(String_Init(&str, &alloc, NULL));
    String_Init(&str, &alloc, "hello");

    CHECK_TRUE(String_EqRaw(&str, "hello"));

    CHECK_DEATH(String_Deinit(NULL));
    String_Deinit(&str);
}

TEST(StringTest, Copy)
{
    String str1, str2;
    String_Init(&str1, &alloc, "hello");
    String_Init(&str2, &alloc, "world");

    CHECK_DEATH(String_Copy(NULL, &str2));
    CHECK_DEATH(String_Copy(&str1, NULL));
    String_Copy(&str1, &str2);

    CHECK_TRUE(String_EqRaw(&str1, "world"));
    CHECK_TRUE(String_EqRaw(&str2, "world"));

    String_Deinit(&str1);
    String_Deinit(&str2);
}

TEST(StringTest, CopyRaw)
{
    String str1;
    String_Init(&str1, &alloc, "hello");

    CHECK_DEATH(String_CopyRaw(NULL, "world"));
    CHECK_DEATH(String_CopyRaw(&str1, NULL));
    String_CopyRaw(&str1, "world");

    CHECK_TRUE(String_EqRaw(&str1, "world"));

    String_Deinit(&str1);
}

TEST(StringTest, Concat)
{
    String str1, str2;
    String_Init(&str1, &alloc, "hello ");
    String_Init(&str2, &alloc, "world");

    CHECK_DEATH(String_Concat(NULL, &str2));
    CHECK_DEATH(String_Concat(&str1, NULL));
    String_Concat(&str1, &str2);

    CHECK_TRUE(String_EqRaw(&str1, "hello world"));
    CHECK_TRUE(String_EqRaw(&str2, "world"));

    String_Deinit(&str1);
    String_Deinit(&str2);
}

TEST(StringTest, ConcatRaw)
{
    String str1;
    String_Init(&str1, &alloc, "hello ");

    CHECK_DEATH(String_ConcatRaw(NULL, "world"));
    CHECK_DEATH(String_ConcatRaw(&str1, NULL));
    String_ConcatRaw(&str1, "world");

    CHECK_TRUE(String_EqRaw(&str1, "hello world"));

    String_Deinit(&str1);
}

TEST(StringTest, Eq)
{
    String str1, str2;
    String_Init(&str1, &alloc, "hello");
    String_Init(&str2, &alloc, "world");

    CHECK_DEATH(String_Eq(NULL, &str2));
    CHECK_DEATH(String_Eq(&str1, NULL));
    CHECK_FALSE(String_Eq(&str1, &str2));
    String_CopyRaw(&str2, "hello");
    CHECK_TRUE(String_Eq(&str1, &str2));

    String_Deinit(&str1);
    String_Deinit(&str2);
}

TEST_SETUP(StringTest) 
{
    ADD_TEST(StringTest, InitDeinit);
    ADD_TEST(StringTest, Copy);
    ADD_TEST(StringTest, CopyRaw);
    ADD_TEST(StringTest, Concat);
    ADD_TEST(StringTest, ConcatRaw);
    ADD_TEST(StringTest, Eq);
}

TEST_BRINGUP(StringTest) { DefaultAllocator_Create(&alloc); }
TEST_TEARDOWN(StringTest) {}
