#pragma once
#include "Hittable.hpp"

namespace rtx {

class Sphere: public IHittable
{
public:
    Sphere(glm::vec3 cen, float r, const IMaterial& m);

    bool hit(const Ray&, float, float, HitRecord&) const override;

private:
    glm::vec3 center_;
    float radius_;
    const IMaterial* mat_ptr_;
};

}  // namespace rtx

