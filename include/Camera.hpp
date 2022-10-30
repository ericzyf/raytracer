#pragma once
#include "Ray.hpp"

namespace rtx {

class Camera
{
public:
    Camera(
        glm::vec3 lookfrom,
        glm::vec3 lookat,
        glm::vec3 vup,
        float vfov,
        float aspect_ratio,
        float aperture,
        float focus_dist
    );

    Ray get_ray(float s, float t) const;

private:
    glm::vec3 origin_;
    glm::vec3 ll_corner_;
    glm::vec3 horizontal_;
    glm::vec3 vertical_;
    glm::vec3 u_;
    glm::vec3 v_;
    glm::vec3 w_;
    float lens_radius_;
};

}  // namespace rtx

