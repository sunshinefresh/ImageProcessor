/**
 * @file GrayscaleFilter.cpp
 */

#include "GrayscaleFilter.h"

#include <algorithm>
#include <thread>
#include <vector>

namespace ip {

void GrayscaleFilter::apply(
    ImageBuffer& image,
    unsigned int threadCount
) {
    if (image.empty()) {
        return;
    }

    const unsigned int maxThreadCount =
        static_cast<unsigned int>(image.height());

    threadCount = std::max(
        1U,
        std::min(threadCount, maxThreadCount)
    );

    if (threadCount == 1) {
        processRows(image, 0, image.height());
        return;
    }

    std::vector<std::thread> workers;
    workers.reserve(threadCount);

    const int rowsPerThread =
        image.height() / static_cast<int>(threadCount);

    const int remainingRows =
        image.height() % static_cast<int>(threadCount);

    int startY = 0;

    for (unsigned int i = 0; i < threadCount; ++i) {
        const int rowCount =
            rowsPerThread + (i < static_cast<unsigned int>(remainingRows) ? 1 : 0);

        const int endY = startY + rowCount;

        workers.emplace_back(
            [this, &image, startY, endY]() {
                processRows(image, startY, endY);
            }
        );

        startY = endY;
    }

    for (std::thread& worker : workers) {
        worker.join();
    }
}

std::string GrayscaleFilter::name() const {
    return "grayscale";
}

void GrayscaleFilter::processRows(
    ImageBuffer& image,
    int startY,
    int endY
) {
    for (int y = startY; y < endY; ++y) {
        std::uint8_t* row = image.rowPtr(y);

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

            row[pixelOffset] = gray;
            row[pixelOffset + 1] = gray;
            row[pixelOffset + 2] = gray;
        }
    }
}

} // namespace ip