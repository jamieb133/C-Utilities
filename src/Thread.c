#ifdef __linux__
#include "posix/Thread.c"
#elif __APPLE__
#include "posix/Thread.c"
#elif _WIN32
#include "win32/Thread.c"
#else
#error "Thread.c not supported on this system"
#endif

