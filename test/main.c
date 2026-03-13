#include <TestFramework.h>

INCLUDE_TEST_SUITE(DummyTest)
INCLUDE_TEST_SUITE(RingBuffer);

int main()
{
    ADD_TEST_SUITE(DummyTest);
    ADD_TEST_SUITE(RingBuffer);

    return RunAllTests(LOG_TEST);
}

