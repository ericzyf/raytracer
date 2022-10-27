#include "Hittable.hpp"
#include <glm/glm.hpp>

namespace rtx {

void HitRecord::set_face_normal(const Ray& r, glm::vec3 outward_normal)
{
    front_face = glm::dot(r.direction(), outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
}

HittableList::HittableList(std::unique_ptr<Hittable> obj)
{
    add(std::move(obj));
}

void HittableList::clear()
{
    objects_.clear();
}

void HittableList::add(std::unique_ptr<Hittable> obj)
{
    objects_.push_back(std::move(obj));
}

bool HittableList::hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const
{
    HitRecord temp_rec;
    bool hit_any = false;
    float closest_so_far = t_max;

    for (const auto& object : objects_) {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_any = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_any;
}

}  // namespace rtx

