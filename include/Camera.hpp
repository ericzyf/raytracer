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
        float aspect_ratio
    );

    Ray get_ray(float u, float v) const;

private:
    glm::vec3 origin_;
    glm::vec3 ll_corner_;
    glm::vec3 horizontal_;
    glm::vec3 vertical_;
};

}  // namespace rtx

