#pragma once

/**
 * @file ConvolutionFilter.h
 * @brief 3x3 Convolution 필터.
 */

#include "FilterBase.h"

namespace ip {

enum class ConvolutionType {
    Blur,
    Sharpen
};

class ConvolutionFilter : public FilterBase {
public:
    explicit ConvolutionFilter(ConvolutionType type);

    void apply(
        ImageBuffer& image,
        unsigned int threadCount
    ) override;

    std::string name() const override;

private:
    ConvolutionType type_;
};

} // namespace ip