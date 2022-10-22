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

}  // namespace rtx
