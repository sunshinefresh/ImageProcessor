#pragma once

/**
 * @file BrightnessFilter.h
 */

#include "FilterBase.h"

namespace ip {

class BrightnessFilter : public FilterBase {
public:
    explicit BrightnessFilter(int amount);

    void apply(
        ImageBuffer& image,
        unsigned int threadCount
    ) override;

    std::string name() const override;

private:
    int amount_;
};

} // namespace ip