/**
 * @file ResizeFilter.cpp
 */

#include "ResizeFilter.h"

#include "Exceptions.h"

#include <utility>

namespace ip {

ResizeFilter::ResizeFilter(
    int width,
    int height
)
    : width_(width),
    height_(height)
{
}

void ResizeFilter::apply(
    ImageBuffer& image,
    unsigned int threadCount
) {
    static_cast<void>(threadCount);

    if (width_ <= 0 || height_ <= 0) {
        throw FilterError(
            "Resize width and height must be positive"
        );
    }

    ImageBuffer resized(width_, height_);

    for (int y = 0; y < height_; ++y) {
        const int srcY =
            y * image.height() / height_;

        const std::uint8_t* srcRow =
            image.rowPtr(srcY);

        std::uint8_t* dstRow =
            resized.rowPtr(y);

        for (int x = 0; x < width_; ++x) {
            const int srcX =
                x * image.width() / width_;

            const int srcOffset =
                srcX * ImageBuffer::CHANNELS;

            const int dstOffset =
                x * ImageBuffer::CHANNELS;

            for (int channel = 0;
                channel < ImageBuffer::CHANNELS;
                ++channel) {

                dstRow[dstOffset + channel] =
                    srcRow[srcOffset + channel];
            }
        }
    }

    image = std::move(resized);
}

std::string ResizeFilter::name() const {
    return
        "resize:" +
        std::to_string(width_) + "," +
        std::to_string(height_);
}

} // namespace ip