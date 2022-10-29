#include "rtweekend.hpp"
#include "debug.hpp"
#include "Rand.hpp"
#include <glm/glm.hpp>
#include <random>
#include <thread>

class ThreadLocalRand: public rtx::Rand
{
public:
    ThreadLocalRand()
        : rtx::Rand(std::hash<std::thread::id>{}(std::this_thread::get_id()))
    {

    }
};

static thread_local ThreadLocalRand _tlrand;

float random_float()
{
    return std::uniform_real_distribution<float>{}(_tlrand);
}

float random_float(float min, float max)
{
    debug_assert(min <= max);
    return min + (max - min) * random_float();
}

glm::vec3 random_in_unit_sphere()
{
    for (;;) {
        const auto p = glm::vec3(
            random_float(-1, 1),
            random_float(-1, 1),
            random_float(-1, 1)
        );

        if (glm::dot(p, p) < 1.0f) {
            return p;
        }
    }
}

glm::vec3 random_unit_vec3()
{
    return glm::normalize(random_in_unit_sphere());
}

bool near_zero_vec3(glm::vec3 v)
{
    using std::fabs;

    constexpr float s = 1e-8;
    return fabs(v[0]) < s &&
           fabs(v[1]) < s &&
           fabs(v[2]) < s;
}
