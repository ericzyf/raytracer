#pragma once
#include "Ray.hpp"
#include <memory>
#include <vector>

namespace rtx {

struct HitRecord
{
    glm::vec3 p;
    glm::vec3 normal;
    float t;
    bool front_face;

    void set_face_normal(const Ray& r, glm::vec3 outward_normal);
};

class Hittable
{
public:
    virtual bool
    hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const = 0;
};

class HittableList: public Hittable
{
public:
    HittableList() = default;

    explicit HittableList(std::unique_ptr<Hittable> obj);

    void clear();

    void add(std::unique_ptr<Hittable> obj);

    bool hit(const Ray&, float, float, HitRecord&) const override;

private:
    std::vector<std::unique_ptr<Hittable>> objects_;
};

}  // namespace rtx

