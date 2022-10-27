#include "Hittable.hpp"
#include <glm/glm.hpp>

namespace rtx {

void HitRecord::set_face_normal(const Ray& r, glm::vec3 outward_normal)
{
    front_face = glm::dot(r.direction(), outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
}

}  // namespace rtx

