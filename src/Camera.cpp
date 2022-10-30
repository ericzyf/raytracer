#include "Camera.hpp"
#include "debug.hpp"
#include "rtweekend.hpp"
#include <glm/glm.hpp>
#include <cmath>

namespace rtx {

Camera::Camera(
    glm::vec3 lookfrom,
    glm::vec3 lookat,
    glm::vec3 vup,
    float vfov,
    float aspect_ratio
)
{
    const auto theta = degrees_to_radians(vfov);
    const auto h = std::tan(theta / 2);
    const auto viewport_height = 2 * h;
    const auto viewport_width = aspect_ratio * viewport_height;

    const auto w = glm::normalize(lookfrom - lookat);
    const auto u = glm::normalize(glm::cross(vup, w));
    const auto v = glm::cross(w, u);

    origin_ = lookfrom;
    horizontal_ = viewport_width * u;
    vertical_ = viewport_height * v;
    ll_corner_ = origin_ - horizontal_ / 2.0f - vertical_ / 2.0f - w;
}

Ray Camera::get_ray(float u, float v) const
{
    return {
        origin_,
        ll_corner_ + u * horizontal_ + v * vertical_ - origin_
    };
}

}  // namespace rtx

