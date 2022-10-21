#include "debug.hpp"

#ifdef __linux__
# include <execinfo.h>
#endif
#include <cstdio>
#include <cstdlib>

void panic_impl(const char* file, int line, const char* msg)
{
    if (msg) {
        std::fprintf(stderr, "\n! Panicked at \'%s\', %s:%d\n", msg, file, line);
    } else {
        std::fprintf(stderr, "\n! Panicked at %s:%d\n", file, line);
    }

#ifdef __linux__
    // get backtrace
    void* bt[10];
    const int num_bt = backtrace(bt, 10);
    const auto symbols = backtrace_symbols(bt, num_bt);

    // print backtrace
    std::fprintf(stderr, "+ stack backtrace:\n");
    for (int i = 0; i < num_bt; ++i) {
        std::fprintf(stderr, "  %d: %s\n", i, symbols[i]);
    }
#endif

    std::abort();
}

