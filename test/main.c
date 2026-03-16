#include <TestFramework.h>

INCLUDE_TEST_SUITE(DummyTest)
INCLUDE_TEST_SUITE(RingBuffer);
INCLUDE_TEST_SUITE(ThreadTest);

int main()
{
    ADD_TEST_SUITE(DummyTest);
    ADD_TEST_SUITE(RingBuffer);
    ADD_TEST_SUITE(ThreadTest);

    return RunAllTests(LOG_TEST);
}

