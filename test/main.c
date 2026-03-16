#include <TestFramework.h>

INCLUDE_TEST_SUITE(DummyTest)
INCLUDE_TEST_SUITE(ArrayTest);
INCLUDE_TEST_SUITE(StringTest);
INCLUDE_TEST_SUITE(RingBuffer);
INCLUDE_TEST_SUITE(ThreadTest);
INCLUDE_TEST_SUITE(ThreadPoolTest);
INCLUDE_TEST_SUITE(ConcurrentQueueTest);

int main()
{
    ADD_TEST_SUITE(DummyTest);
    ADD_TEST_SUITE(ArrayTest);
    ADD_TEST_SUITE(StringTest);
    ADD_TEST_SUITE(RingBuffer);
    ADD_TEST_SUITE(ThreadTest);
    ADD_TEST_SUITE(ThreadPoolTest);
    ADD_TEST_SUITE(ConcurrentQueueTest);

    return RunAllTests(LOG_TEST);
}

