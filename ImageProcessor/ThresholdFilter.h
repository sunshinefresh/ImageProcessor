#pragma once

/**
 * @file ThresholdFilter.h
 */

#include "FilterBase.h"

namespace ip {

class ThresholdFilter : public FilterBase {
public:
    explicit ThresholdFilter(std::uint8_t threshold);

    void apply(
        ImageBuffer& image,
        unsigned int threadCount
    ) override;

    std::string name() const override;

private:
    void processRows(
        ImageBuffer& image,
        int startY,
        int endY
    );

    std::uint8_t threshold_;
};

} // namespace ip