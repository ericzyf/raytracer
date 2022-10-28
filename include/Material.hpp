#pragma once
#include "Hittable.hpp"

namespace rtx {

class IMaterial
{
public:
    virtual bool scatter(
        const Ray& r_in,
        const HitRecord& rec,
        glm::vec3& attenuation,
        Ray& scattered
    ) const = 0;
};

}  // namespace rtx

