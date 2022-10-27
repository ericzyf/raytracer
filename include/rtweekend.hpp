#pragma once
#include <limits>

constexpr float infinity = std::numeric_limits<float>::infinity();
constexpr float pi = 3.1415926535897932385f;

inline float degrees_to_radians(float deg)
{
    return deg * pi / 180.0f;
}

float random_float();

float random_float(float min, float max);

