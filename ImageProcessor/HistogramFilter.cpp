/**
 * @file HistogramFilter.cpp
 */

#include "HistogramFilter.h"

#include <array>
#include <iostream>

namespace ip {

void HistogramFilter::apply(
    ImageBuffer& image,
    unsigned int threadCount
) {
    if (image.empty()) {
        return;
    }

    static_cast<void>(threadCount);

    std::array<std::size_t, 256> histogram{};

    for (int y = 0; y < image.height(); ++y) {
        const std::uint8_t* row = image.rowPtr(y);

        for (int x = 0; x < image.width(); ++x) {
            const int pixelOffset = x * ImageBuffer::CHANNELS;

            const std::uint8_t b = row[pixelOffset];
            const std::uint8_t g = row[pixelOffset + 1];
            const std::uint8_t r = row[pixelOffset + 2];

            const std::uint8_t gray = static_cast<std::uint8_t>(
                0.114 * b +
                0.587 * g +
                0.299 * r
                );

            ++histogram[gray];
        }
    }

    std::cout << "Intensity,Count\n";

    for (std::size_t i = 0; i < histogram.size(); ++i) {
        std::cout
            << i
            << ","
            << histogram[i]
            << "\n";
    }
}

std::string HistogramFilter::name() const {
    return "histogram";
}

} // namespace ip