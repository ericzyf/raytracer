#include "rtweekend.hpp"
#include "Camera.hpp"
#include "Pixmap.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"
#include <fmt/core.h>
#include <glm/glm.hpp>

using namespace rtx;

glm::vec3 ray_color(const Ray& r, const Hittable& world)
{
    HitRecord rec;
    if (world.hit(r, 0, infinity, rec)) {
        return 0.5f * (rec.normal + glm::vec3(1));
    }

    glm::vec3 unit_direction = glm::normalize(r.direction());
    const auto t = 0.5f * (unit_direction.y + 1.0f);
    return (1.0f - t) * glm::vec3(1) + t * glm::vec3(0.5, 0.7, 1.0);
}

int main(int argc, char* argv[])
{
    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 1280;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;

    // World
    HittableList world;
    world.add(std::make_unique<Sphere>(glm::vec3(0, 0, -1), 0.5f));
    world.add(std::make_unique<Sphere>(glm::vec3(0, -100.5f, -1), 100.0f));

    // Camera
    Camera cam;

    // Render
    Pixmap pm(image_width, image_height);
    for (int j = image_height - 1; j >= 0; --j) {
        fmt::print(stderr, "Scanlines remaining: {}\n", j);
        for (int i = 0; i < image_width; ++i) {
            auto pixel_color = glm::vec3(0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + random_float()) / (image_width - 1);
                auto v = (j + random_float()) / (image_height - 1);
                auto r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world);
            }
            pm.data()[j * pm.width() + i] =
                RGB(pixel_color / static_cast<float>(samples_per_pixel));
        }
    }

    pm.write_bmp("image.bmp");
}

