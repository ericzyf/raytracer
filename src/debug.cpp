#include "debug.hpp"
#include <cstdio>
#include <cstdlib>

void panic_impl(const char* file, int line, const char* msg)
{
    if (msg) {
        std::fprintf(stderr, "\n! Panicked at \'%s\', %s:%d\n", msg, file, line);
    } else {
        std::fprintf(stderr, "\n! Panicked at %s:%d\n", file, line);
    }
    std::abort();
}

