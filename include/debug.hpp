#pragma once

#define panic()         panic_impl(__FILE__, __LINE__)
#define panic_with(msg) panic_impl(__FILE__, __LINE__, msg)

#ifdef NDEBUG
# define debug_assert(cond) ((void)0)
#else
# define debug_assert(cond) do {\
    if (!(cond)) panic_with("assertion failed: " #cond);\
} while (0)
#endif

[[noreturn]]
void panic_impl(const char* file, int line, const char* msg = nullptr);

