#pragma once
#include "Ray.hpp"

namespace rtx {

class Camera
{
public:
    Camera();

    Ray get_ray(float u, float v) const;

private:
    glm::vec3 origin_;
    glm::vec3 ll_corner_;
    glm::vec3 horizontal_;
    glm::vec3 vertical_;
};

}  // namespace rtx

