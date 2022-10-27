#include "Camera.hpp"
#include "debug.hpp"

namespace rtx {

Camera::Camera()
{
    constexpr auto aspect_ratio = 16.0f / 9.0f;
    constexpr auto viewport_height = 2.0f;
    constexpr auto viewport_width = aspect_ratio * viewport_height;
    constexpr auto focal_length = 1.0f;

    origin_ = glm::vec3(0);
    horizontal_ = glm::vec3(viewport_width, 0, 0);
    vertical_ = glm::vec3(0, viewport_height, 0);
    ll_corner_ =
        origin_ - horizontal_ / 2.0f - vertical_ / 2.0f - glm::vec3(0, 0, focal_length);
}

Ray Camera::get_ray(float u, float v) const
{
    return {
        origin_,
        ll_corner_ + u * horizontal_ + v * vertical_ - origin_
    };
}

}  // namespace rtx

