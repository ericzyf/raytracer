#pragma once
#include <memory>

namespace rtx {

struct RGB
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

class Pixmap
{
public:
    Pixmap(unsigned w, unsigned h);

    unsigned width() const;

    unsigned height() const;

private:
    unsigned width_;
    unsigned height_;
    unsigned size_;
    std::unique_ptr<RGB[]> buf_;
};

}  // namespace rtx
