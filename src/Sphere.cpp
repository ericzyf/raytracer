#include "Sphere.hpp"
#include <glm/glm.hpp>

namespace rtx {

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
    rec.normal = (rec.p - center_) / radius_;
    return true;
}

}  // namespace rtx

