#include <TestFramework.h>

INCLUDE_TEST_SUITE(DummyTest)

int main()
{
    ADD_TEST_SUITE(DummyTest);

    return RunAllTests(LOG_TEST);
}

