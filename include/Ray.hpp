#pragma once
#include <glm/vec3.hpp>

namespace rtx {

class Ray
{
public:
    Ray() = default;

    Ray(glm::vec3 origin, glm::vec3 direction)
        : origin_(origin),
          direction_(direction)
    {

    }

    glm::vec3 origin() const
    {
        return origin_;
    }

    glm::vec3 direction() const
    {
        return direction_;
    }

    glm::vec3 at(const float t) const
    {
        return origin_ + t * direction_;
    }

private:
    glm::vec3 origin_;
    glm::vec3 direction_;
};

}  // namespace rtx
