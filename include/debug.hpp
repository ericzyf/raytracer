#pragma once

#define panic()         panic_impl(__FILE__, __LINE__)
#define panic_with(msg) panic_impl(__FILE__, __LINE__, msg)

[[noreturn]]
void panic_impl(const char* file, int line, const char* msg = nullptr);

