#pragma once
#include <limits>
#include <glm/vec3.hpp>

constexpr float infinity = std::numeric_limits<float>::infinity();
constexpr float pi = 3.1415926535897932385f;

inline float degrees_to_radians(float deg)
{
    return deg * pi / 180.0f;
}

float random_float();

float random_float(float min, float max);

glm::vec3 random_in_unit_sphere();

glm::vec3 random_unit_vec3();

bool near_zero_vec3(glm::vec3 v);

