#include "rtweekend.hpp"
#include "Pixmap.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"
#include <fmt/core.h>
#include <glm/glm.hpp>

using namespace rtx;

RGB ray_color(const Ray& r, const Hittable& world)
{
    HitRecord rec;
    if (world.hit(r, 0, infinity, rec)) {
        return RGB(0.5f * (rec.normal + glm::vec3(1)));
    }

    glm::vec3 unit_direction = glm::normalize(r.direction());
    const auto t = 0.5f * (unit_direction.y + 1.0f);
    return RGB((1.0f - t) * glm::vec3(1) + t * glm::vec3(0.5, 0.7, 1.0));
}

int main(int argc, char* argv[])
{
    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 1280;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // World
    HittableList world;
    world.add(std::make_unique<Sphere>(glm::vec3(0, 0, -1), 0.5f));
    world.add(std::make_unique<Sphere>(glm::vec3(0, -100.5f, -1), 100.0f));

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
            pm.data()[j * pm.width() + i] = ray_color(r, world);
        }
    }

    pm.write_bmp("image.bmp");
}

