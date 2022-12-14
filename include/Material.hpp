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

class Dielectric: public IMaterial
{
public:
    explicit Dielectric(float ir)
        : ir_(ir)
    {
        debug_assert(ir > 0.0f);
    }

    bool scatter(
        const Ray& r_in,
        const HitRecord& rec,
        glm::vec3& attenuation,
        Ray& scattered
    ) const override
    {
        attenuation = glm::vec3(1);
        const float refraction_ratio = rec.front_face ? (1.0f / ir_) : ir_;

        const auto unit_direction = glm::normalize(r_in.direction());
        const float cos_theta = glm::dot(-unit_direction, rec.normal);
        const float sin_theta = std::sqrt(1.0f - cos_theta * cos_theta);

        glm::vec3 direction;
        const bool cannot_refract =
            refraction_ratio * sin_theta > 1.0f ||
            reflectance(cos_theta, refraction_ratio) > random_float();
        if (cannot_refract) {
            direction = glm::reflect(unit_direction, rec.normal);
        } else {
            direction = glm::refract(unit_direction, rec.normal, refraction_ratio);
        }

        scattered = { rec.p, direction };
        return true;
    }

private:
    float ir_;

    static float reflectance(float cosine, float ref_idx)
    {
        // Use Schlick's approximation for reflectance.
        auto r0 = (1 - ref_idx) / (1 + ref_idx);
        r0 *= r0;
        return r0 + (1 - r0) * std::pow(1 - cosine, 5);
    }
};

}  // namespace Material

}  // namespace rtx

