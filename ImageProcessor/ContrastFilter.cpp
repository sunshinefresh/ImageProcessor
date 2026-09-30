/**
 * @file ContrastFilter.cpp
 */

#include "ContrastFilter.h"

#include <algorithm>

namespace ip {

ContrastFilter::ContrastFilter(double factor)
    : factor_(factor)
{
}

void ContrastFilter::apply(
    ImageBuffer& image,
    unsigned int threadCount
) {
    if (image.empty()) {
        return;
    }

    static_cast<void>(threadCount);

    for (int y = 0; y < image.height(); ++y) {
        std::uint8_t* row = image.rowPtr(y);

        for (int x = 0; x < image.width(); ++x) {
            const int pixelOffset = x * ImageBuffer::CHANNELS;

            for (int channel = 0; channel < ImageBuffer::CHANNELS; ++channel) {
                const double adjusted =
                    (static_cast<double>(row[pixelOffset + channel]) - 128.0)
                    * factor_ + 128.0;

                const int value =
                    static_cast<int>(adjusted);

                row[pixelOffset + channel] =
                    static_cast<std::uint8_t>(
                        std::clamp(value, 0, 255)
                        );
            }
        }
    }
}

std::string ContrastFilter::name() const {
    return "contrast:" + std::to_string(factor_);
}

} // namespace ip