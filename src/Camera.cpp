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
    float aspect_ratio,
    float aperture,
    float focus_dist
)
{
    const auto theta = degrees_to_radians(vfov);
    const auto h = std::tan(theta / 2);
    const auto viewport_height = 2 * h;
    const auto viewport_width = aspect_ratio * viewport_height;

    w_ = glm::normalize(lookfrom - lookat);
    u_ = glm::normalize(glm::cross(vup, w_));
    v_ = glm::cross(w_, u_);

    origin_ = lookfrom;
    horizontal_ = focus_dist * viewport_width * u_;
    vertical_ = focus_dist * viewport_height * v_;
    ll_corner_ = origin_ - horizontal_ / 2.0f - vertical_ / 2.0f - focus_dist * w_;
    lens_radius_ = aperture / 2;
}

Ray Camera::get_ray(float s, float t) const
{
    const auto rd = lens_radius_ * random_in_unit_disk();
    const auto offset = rd.x * u_ + rd.y * v_;
    return {
        origin_ + offset,
        ll_corner_ + s * horizontal_ + t * vertical_ - origin_ - offset
    };
}

}  // namespace rtx

