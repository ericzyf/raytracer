#include "debug.hpp"
#include "Pixmap.hpp"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>
#include <cstring>

namespace rtx {

RGB::RGB(const glm::vec3 v)
    : r(v.r * 255.999),
      g(v.g * 255.999),
      b(v.b * 255.999)
{
    debug_assert(v.r >= 0 && v.r < 1);
    debug_assert(v.g >= 0 && v.g < 1);
    debug_assert(v.b >= 0 && v.b < 1);
}

Pixmap::Pixmap(unsigned w, unsigned h)
    : width_(w),
      height_(h),
      size_(w * h),
      buf_(std::make_unique<RGB[]>(size_))
{

}

unsigned Pixmap::width() const
{
    return width_;
}

unsigned Pixmap::height() const
{
    return height_;
}

unsigned Pixmap::size() const
{
    return size_;
}

RGB* Pixmap::data()
{
    return buf_.get();
}

const RGB* Pixmap::data() const
{
    return buf_.get();
}

void Pixmap::clear()
{
    std::memset(data(), 0, size_ * sizeof(RGB));
}

bool Pixmap::write_bmp(const char* path, bool flip_y) const
{
    debug_assert(path);

    stbi_flip_vertically_on_write(flip_y);
    return stbi_write_bmp(path, width_, height_, 3, data()) != 0;
}

}  // namespace rtx

