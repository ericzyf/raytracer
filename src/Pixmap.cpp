#include "debug.hpp"
#include "Pixmap.hpp"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

namespace rtx {

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

bool Pixmap::write_bmp(const char* path, bool flip_y) const
{
    debug_assert(path);

    stbi_flip_vertically_on_write(flip_y);
    return stbi_write_bmp(path, width_, height_, 3, data()) != 0;
}

}  // namespace rtx

