#include "rtweekend.hpp"
#include "debug.hpp"
#include "Rand.hpp"
#include <random>

static rtx::Rand _rand;

float random_float()
{
    static std::uniform_real_distribution<float> dist;
    return dist(_rand);
}

float random_float(float min, float max)
{
    debug_assert(min <= max);
    return min + (max - min) * random_float();
}

