#include "rtweekend.hpp"
#include "debug.hpp"
#include "Camera.hpp"
#include "Pixmap.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"
#include <fmt/core.h>
#include <glm/glm.hpp>
#include <thread>

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
    constexpr int samples_per_pixel = 100;

    // World
    HittableList world;
    world.add(std::make_unique<Sphere>(glm::vec3(0, 0, -1), 0.5f));
    world.add(std::make_unique<Sphere>(glm::vec3(0, -100.5f, -1), 100.0f));

    // Camera
    Camera cam;

    // Render
    Pixmap pm(image_width, image_height);

    float du[samples_per_pixel];
    float dv[samples_per_pixel];
    for (int i = 0; i < samples_per_pixel; ++i) {
        du[i] = random_float();
        dv[i] = random_float();
    }

    auto render_row = [&](const int row)
    {
        debug_assert(row >= 0);
        debug_assert(row < pm.height());

        auto row_pm = pm.data() + row * pm.width();
        for (int i = 0; i < image_width; ++i) {
            auto pixel_color = glm::vec3(0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + du[s]) / (image_width - 1);
                auto v = (row + dv[s]) / (image_height - 1);
                auto r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world);
            }
            *row_pm++ =
                RGB(pixel_color / static_cast<float>(samples_per_pixel));
        }
    };

    auto render_row_range = [&](int begin, int end)
    {
        debug_assert(begin <= end);

        for (; begin < end; ++begin) {
            render_row(begin);
        }
    };

    const int num_threads = std::thread::hardware_concurrency();
    debug_assert(num_threads > 0);

    std::vector<std::thread> workers;
    workers.reserve(num_threads);

    // Dispatch render tasks
    for (int i = 0, curr_row = 0; i < num_threads; ++i) {
        const int num_rows = image_height / num_threads + (i < image_height % num_threads);
        workers.emplace_back(render_row_range, curr_row, curr_row + num_rows);
        curr_row += num_rows;
    }

    // Join
    for (auto& worker : workers) {
        worker.join();
    }

    pm.write_bmp("image.bmp");
}

