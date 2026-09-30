#pragma once

/**
 * @file HistogramFilter.h
 * @brief 이미지 밝기 히스토그램 분석.
 */

#include "FilterBase.h"

namespace ip {

class HistogramFilter : public FilterBase {
public:
    void apply(
        ImageBuffer& image,
        unsigned int threadCount
    ) override;

    std::string name() const override;
};

} // namespace ip