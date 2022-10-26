#pragma once
#include "Ray.hpp"

namespace rtx {

struct HitRecord
{
    glm::vec3 p;
    glm::vec3 normal;
    float t;
};

class Hittable
{
public:
    virtual bool
    hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const = 0;
};

}  // namespace rtx

