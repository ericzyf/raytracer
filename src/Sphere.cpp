#include "debug.hpp"
#include "Sphere.hpp"
#include <glm/glm.hpp>

namespace rtx {

Sphere::Sphere(glm::vec3 cen, float r, const IMaterial& m)
    : center_(cen),
      radius_(r),
      mat_ptr_(&m)
{
    debug_assert(r > 0);
}

bool Sphere::hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const
{
    glm::vec3 oc = r.origin() - center_;
    auto a = glm::dot(r.direction(), r.direction());
    auto h = glm::dot(oc, r.direction());
    auto c = glm::dot(oc, oc) - radius_ * radius_;

    const auto discriminant = h * h - a * c;
    if (discriminant < 0) {
        return false;
    }
    const auto sqrtd = std::sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-h - sqrtd) / a;
    if (root < t_min || root > t_max) {
        root = (-h + sqrtd) / a;
        if (root < t_min || root > t_max) {
            return false;
        }
    }

    rec.t = root;
    rec.p = r.at(root);
    const auto outward_normal = (rec.p - center_) / radius_;
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr_;
    return true;
}

}  // namespace rtx

