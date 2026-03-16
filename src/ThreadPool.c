#ifdef __linux__
#include "posix/ThreadPool.c"
#elif __APPLE__
#include "posix/ThreadPool.c"
#elif _WIN32
#include "win32/ThreadPool.c"
#else
#error "ThreadPool.c not supported on this system"
#endif
