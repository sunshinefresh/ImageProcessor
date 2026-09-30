/**
 * @file BrightnessFilter.cpp
 */

#include "BrightnessFilter.h"

#include <algorithm>

namespace ip {

BrightnessFilter::BrightnessFilter(int amount)
    : amount_(amount)
{
}

void BrightnessFilter::apply(
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
                const int value =
                    static_cast<int>(row[pixelOffset + channel]) + amount_;

                row[pixelOffset + channel] =
                    static_cast<std::uint8_t>(
                        std::clamp(value, 0, 255)
                        );
            }
        }
    }
}

std::string BrightnessFilter::name() const {
    return "brightness:" + std::to_string(amount_);
}

} // namespace ip