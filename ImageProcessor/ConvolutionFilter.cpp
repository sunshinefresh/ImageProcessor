/**
 * @file ConvolutionFilter.cpp
 */

#include "ConvolutionFilter.h"

#include <algorithm>
#include <array>

namespace ip {

namespace {

constexpr std::array<int, 9> BLUR_KERNEL = {
    1, 1, 1,
    1, 1, 1,
    1, 1, 1
};

constexpr std::array<int, 9> SHARPEN_KERNEL = {
        0, -1,  0,
    -1,  5, -1,
        0, -1,  0
};

} // anonymous namespace

ConvolutionFilter::ConvolutionFilter(ConvolutionType type)
    : type_(type)
{
}

void ConvolutionFilter::apply(
    ImageBuffer& image,
    unsigned int threadCount
) {
    if (image.empty()) {
        return;
    }

    static_cast<void>(threadCount);

    if (image.width() < 3 || image.height() < 3) {
        return;
    }

    const ImageBuffer source = image;

    const std::array<int, 9>& kernel =
        (type_ == ConvolutionType::Blur)
        ? BLUR_KERNEL
        : SHARPEN_KERNEL;

    const int divisor =
        (type_ == ConvolutionType::Blur) ? 9 : 1;

    for (int y = 1; y < image.height() - 1; ++y) {
        std::uint8_t* dstRow = image.rowPtr(y);

        for (int x = 1; x < image.width() - 1; ++x) {
            const int pixelOffset = x * ImageBuffer::CHANNELS;

            for (int channel = 0; channel < ImageBuffer::CHANNELS; ++channel) {
                int sum = 0;
                int kernelIndex = 0;

                for (int ky = -1; ky <= 1; ++ky) {
                    const std::uint8_t* srcRow =
                        source.rowPtr(y + ky);

                    for (int kx = -1; kx <= 1; ++kx) {
                        const int srcOffset =
                            (x + kx) * ImageBuffer::CHANNELS;

                        sum +=
                            static_cast<int>(
                                srcRow[srcOffset + channel]
                                )
                            * kernel[kernelIndex];

                        ++kernelIndex;
                    }
                }

                const int value =
                    std::clamp(sum / divisor, 0, 255);

                dstRow[pixelOffset + channel] =
                    static_cast<std::uint8_t>(value);
            }
        }
    }
}

std::string ConvolutionFilter::name() const {
    if (type_ == ConvolutionType::Blur) {
        return "blur";
    }

    return "sharpen";
}

} // namespace ip