#include "Logger.h"
#include <TestFramework.h>

TEST(DummyTest, Example)
{
    LogTest("Running example test");
    LogTrace("Running example test");
    LogInfo("Running example test");
    LogWarn("Running example test");
    LogError("Running example test");

    CHECK_TRUE(true);
}

TEST_SETUP(DummyTest)
{
    ADD_TEST(DummyTest, Example); 
}

TEST_BRINGUP(DummyTest)
{

}

TEST_TEARDOWN(DummyTest)
{

}

