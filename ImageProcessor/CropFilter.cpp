/**
 * @file CropFilter.cpp
 */

#include "CropFilter.h"

#include "Exceptions.h"

#include <algorithm>
#include <utility>

namespace ip {

CropFilter::CropFilter(
    int x,
    int y,
    int width,
    int height
)
    : x_(x),
    y_(y),
    width_(width),
    height_(height)
{
}

void CropFilter::apply(
    ImageBuffer& image,
    unsigned int threadCount
) {
    static_cast<void>(threadCount);

    if (
        x_ < 0 ||
        y_ < 0 ||
        width_ <= 0 ||
        height_ <= 0 ||
        x_ + width_ > image.width() ||
        y_ + height_ > image.height()
        ) {
        throw FilterError("Invalid crop area");
    }

    ImageBuffer cropped(width_, height_);

    const int copySize =
        width_ * ImageBuffer::CHANNELS;

    for (int y = 0; y < height_; ++y) {
        const std::uint8_t* srcRow =
            image.rowPtr(y_ + y)
            + x_ * ImageBuffer::CHANNELS;

        std::uint8_t* dstRow =
            cropped.rowPtr(y);

        std::copy_n(
            srcRow,
            copySize,
            dstRow
        );
    }

    image = std::move(cropped);
}

std::string CropFilter::name() const {
    return
        "crop:" +
        std::to_string(x_) + "," +
        std::to_string(y_) + "," +
        std::to_string(width_) + "," +
        std::to_string(height_);
}

} // namespace ip