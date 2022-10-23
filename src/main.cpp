#include "Pixmap.hpp"
#include "Ray.hpp"
#include <fmt/core.h>
#include <glm/glm.hpp>

using namespace rtx;

bool hit_sphere(const glm::vec3 center, float radius, const Ray& r)
{
    glm::vec3 oc = r.origin() - center;
    auto a = glm::dot(r.direction(), r.direction());
    auto b = 2.0f * glm::dot(oc, r.direction());
    auto c = glm::dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;
    return discriminant > 0;
}

RGB ray_color(const Ray& r)
{
    if (hit_sphere(glm::vec3(0, 0, -1), 0.5f, r)) {
        return { 255, 0, 0 };
    }

    auto unit_direction = glm::normalize(r.direction());
    float t = 0.5f * (unit_direction.y + 1.0f);
    return RGB(
        (1.0f - t) * glm::vec3(1.0) + t * glm::vec3(0.5, 0.7, 1.0)
    );
}

int main(int argc, char* argv[])
{
    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // Camera
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = glm::vec3(0);
    auto horizontal = glm::vec3(viewport_width, 0, 0);
    auto vertical = glm::vec3(0, viewport_height, 0);
    auto lower_left_corner =
        origin - horizontal / 2.0f - vertical / 2.0f - glm::vec3(0, 0, focal_length);

    // Render
    Pixmap pm(image_width, image_height);
    for (int j = image_height - 1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            float u = i * 1.0f / (image_width - 1);
            float v = j * 1.0f / (image_height - 1);
            Ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
            pm.data()[j * pm.width() + i] = ray_color(r);
        }
    }

    pm.write_bmp("image.bmp");
}

