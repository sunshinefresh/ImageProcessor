#pragma once

/**
 * @file ResizeFilter.h
 * @brief 이미지 Resize 필터.
 */

#include "FilterBase.h"

namespace ip {

class ResizeFilter : public FilterBase {
public:
    ResizeFilter(
        int width,
        int height
    );

    void apply(
        ImageBuffer& image,
        unsigned int threadCount
    ) override;

    std::string name() const override;

private:
    int width_;
    int height_;
};

} // namespace ip