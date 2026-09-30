/**
 * @file FlipFilter.cpp
 */

#include "FlipFilter.h"

#include <algorithm>

namespace ip {

FlipFilter::FlipFilter(FlipDirection direction)
    : direction_(direction)
{
}

void FlipFilter::apply(
    ImageBuffer& image,
    unsigned int threadCount
) {
    if (image.empty()) {
        return;
    }

    static_cast<void>(threadCount);

    if (direction_ == FlipDirection::Horizontal) {
        for (int y = 0; y < image.height(); ++y) {
            std::uint8_t* row = image.rowPtr(y);

            for (int x = 0; x < image.width() / 2; ++x) {
                const int leftOffset = x * ImageBuffer::CHANNELS;
                const int rightOffset =
                    (image.width() - 1 - x) * ImageBuffer::CHANNELS;

                for (int channel = 0; channel < ImageBuffer::CHANNELS; ++channel) {
                    std::swap(
                        row[leftOffset + channel],
                        row[rightOffset + channel]
                    );
                }
            }
        }
    }
    else {
        const int rowStride = image.rowStride();

        for (int y = 0; y < image.height() / 2; ++y) {
            std::uint8_t* topRow = image.rowPtr(y);
            std::uint8_t* bottomRow =
                image.rowPtr(image.height() - 1 - y);

            for (int i = 0; i < rowStride; ++i) {
                std::swap(topRow[i], bottomRow[i]);
            }
        }
    }
}

std::string FlipFilter::name() const {
    if (direction_ == FlipDirection::Horizontal) {
        return "flip:horizontal";
    }

    return "flip:vertical";
}

} // namespace ip