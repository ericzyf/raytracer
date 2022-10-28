#include "rtweekend.hpp"
#include "debug.hpp"
#include "Rand.hpp"
#include <random>
#include <thread>

class ThreadLocalRand: public rtx::Rand
{
public:
    ThreadLocalRand()
        : rtx::Rand(std::hash<std::thread::id>{}(std::this_thread::get_id()))
    {

    }
};

static thread_local ThreadLocalRand _tlrand;

float random_float()
{
    return std::uniform_real_distribution<float>{}(_tlrand);
}

float random_float(float min, float max)
{
    debug_assert(min <= max);
    return min + (max - min) * random_float();
}

