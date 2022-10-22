#include "Pixmap.hpp"

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

}  // namespace rtx
