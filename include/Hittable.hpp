#pragma once
#include "Ray.hpp"
#include <memory>
#include <vector>

namespace rtx {

class IMaterial;

struct HitRecord
{
    glm::vec3 p;
    glm::vec3 normal;
    const IMaterial* mat_ptr;
    float t;
    bool front_face;

    void set_face_normal(const Ray& r, glm::vec3 outward_normal);
};

class IHittable
{
public:
    virtual bool
    hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const = 0;

    virtual ~IHittable() = default;
};

class HittableList: public IHittable
{
public:
    HittableList() = default;

    explicit HittableList(std::unique_ptr<IHittable> obj);

    void clear();

    void add(std::unique_ptr<IHittable> obj);

    bool hit(const Ray&, float, float, HitRecord&) const override;

private:
    std::vector<std::unique_ptr<IHittable>> objects_;
};

}  // namespace rtx

