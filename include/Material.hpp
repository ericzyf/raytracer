#pragma once
#include "debug.hpp"
#include "rtweekend.hpp"
#include "Hittable.hpp"
#include <glm/glm.hpp>

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

    virtual ~IMaterial() = default;
};

namespace Material {

class Lambertian: public IMaterial
{
public:
    explicit Lambertian(glm::vec3 a)
        : albedo_(a)
    {

    }

    bool scatter(
        const Ray& r_in,
        const HitRecord& rec,
        glm::vec3& attenuation,
        Ray& scattered
    ) const override
    {
        auto scatter_direction = rec.normal + random_unit_vec3();
        // Catch degenerate scatter direction
        if (near_zero_vec3(scatter_direction)) {
            scatter_direction = rec.normal;
        }

        scattered = { rec.p, scatter_direction };
        attenuation = albedo_;
        return true;
    }

private:
    glm::vec3 albedo_;
};

class Metal: public IMaterial
{
public:
    explicit Metal(glm::vec3 a, float f)
        : albedo_(a),
          fuzz_(std::min(1.0f, f))
    {
        debug_assert(fuzz_ >= 0);
    }

    bool scatter(
        const Ray& r_in,
        const HitRecord& rec,
        glm::vec3& attenuation,
        Ray& scattered
    ) const override
    {
        const auto reflected = glm::reflect(
            glm::normalize(r_in.direction()),
            rec.normal
        );

        scattered = {
            rec.p,
            reflected + fuzz_ * random_in_unit_sphere()
        };
        attenuation = albedo_;
        return glm::dot(scattered.direction(), rec.normal) > 0.0f;
    }

private:
    glm::vec3 albedo_;
    float fuzz_;
};

}  // namespace Material

}  // namespace rtx

