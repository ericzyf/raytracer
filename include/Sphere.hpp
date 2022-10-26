#pragma once
#include "Hittable.hpp"

namespace rtx {

class Sphere: public Hittable
{
public:
    Sphere() = default;

    Sphere(glm::vec3 cen, float r)
        : center_(cen),
          radius_(r)
    {

    }

    bool hit(const Ray&, float, float, HitRecord&) const override;

private:
    glm::vec3 center_;
    float radius_;
};

}  // namespace rtx

