#include "rtweekend.hpp"
#include "debug.hpp"
#include "Camera.hpp"
#include "Material.hpp"
#include "Pixmap.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"
#include <fmt/core.h>
#include <glm/glm.hpp>
#include <thread>

using namespace rtx;

glm::vec3 ray_color(const Ray& r, const IHittable& world, int depth)
{
    if (depth <= 0) {
        return glm::vec3(0);
    }

    HitRecord rec;
    if (world.hit(r, 0.001, infinity, rec)) {
        Ray scattered;
        glm::vec3 attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return attenuation * ray_color(scattered, world, depth - 1);
        }
        return glm::vec3(0);
    }

    glm::vec3 unit_direction = glm::normalize(r.direction());
    const auto t = 0.5f * (unit_direction.y + 1.0f);
    return (1.0f - t) * glm::vec3(1) + t * glm::vec3(0.5, 0.7, 1.0);
}

int main(int argc, char* argv[])
{
    // Image
    constexpr auto aspect_ratio = 16.0 / 9.0;
    constexpr int image_width = 1280;
    constexpr int image_height = static_cast<int>(image_width / aspect_ratio);
    constexpr float inv_gamma = 1.0f / 2.2f;
    constexpr int samples_per_pixel = 100;
    constexpr int max_depth = 50;

    // World
    Material::Lambertian material_ground(glm::vec3(0.8, 0.8, 0));
    Material::Dielectric material_center(1.5f);
    Material::Dielectric material_left(1.5f);
    Material::Metal material_right(glm::vec3(0.8, 0.6, 0.2), 1);

    HittableList world;
    world.add(
        std::make_unique<Sphere>(glm::vec3(0, -100.5, -1), 100, material_ground)
    );
    world.add(
        std::make_unique<Sphere>(glm::vec3(0, 0, -1), 0.5, material_center)
    );
    world.add(
        std::make_unique<Sphere>(glm::vec3(-1, 0, -1), 0.5, material_left)
    );
    world.add(
        std::make_unique<Sphere>(glm::vec3(1, 0, -1), 0.5, material_right)
    );

    // Camera
    Camera cam;

    // Render
    struct {
        float x;
        float y;
    } ds[samples_per_pixel];

    for (int i = 0; i < samples_per_pixel; ++i) {
        ds[i].x = random_float();
        ds[i].y = random_float();
    }

    auto render_samples = [&](std::vector<glm::vec3>& pm, const int si, const int sj)
    {
        debug_assert(si >= 0 && si < samples_per_pixel);
        debug_assert(sj >= 0 && sj <= samples_per_pixel);
        debug_assert(si <= sj);

        const auto num_samples = sj - si;
        auto ppm = pm.begin();

        for (int y = 0; y < image_height; ++y) {
            for (int x = 0; x < image_width; ++x) {
                auto pixel_color = glm::vec3(0);
                for (int s = si; s != sj; ++s) {
                    const auto u = (x + ds[s].x) / (image_width - 1);
                    const auto v = (y + ds[s].y) / (image_height - 1);
                    pixel_color += ray_color(
                        cam.get_ray(u, v),
                        world,
                        max_depth
                    );
                }

                // average samples and then apply gamma correction
                *ppm++ = glm::pow(
                    pixel_color / static_cast<float>(num_samples),
                    glm::vec3(inv_gamma)
                );
            }
        }
    };

    const int num_threads = std::thread::hardware_concurrency();
    debug_assert(num_threads > 0);

    std::vector<std::thread> workers;
    workers.reserve(num_threads);

    std::vector<std::vector<glm::vec3>> worker_pm(num_threads);
    for (auto& pm : worker_pm) {
        pm.resize(image_width * image_height);
    }

    // Dispatch render tasks
    for (int i = 0, curr_sample = 0; i < num_threads; ++i) {
        const int num_samples =
            samples_per_pixel / num_threads + (i < samples_per_pixel % num_threads);

        workers.emplace_back(
            render_samples,
            std::ref(worker_pm[i]), curr_sample, curr_sample + num_samples
        );

        curr_sample += num_samples;
    }

    // Join
    for (auto& worker : workers) {
        worker.join();
    }

    // sum pixmaps
    for (int i = 1; i < num_threads; ++i) {
        auto& pm = worker_pm[i];
        for (size_t j = 0; j < pm.size(); ++j) {
            worker_pm[0][j] += pm[j];
        }
    }

    Pixmap pm(image_width, image_height);
    for (size_t i = 0, n = image_width * image_height; i < n; ++i) {
        pm.data()[i] = RGB(worker_pm[0][i] / static_cast<float>(num_threads));
    }

    pm.write_bmp("image.bmp");
}

