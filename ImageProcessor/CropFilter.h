#pragma once

/**
 * @file CropFilter.h
 * @brief 이미지 Crop 필터.
 */

#include "FilterBase.h"

namespace ip {

class CropFilter : public FilterBase {
public:
    CropFilter(
        int x,
        int y,
        int width,
        int height
    );

    void apply(
        ImageBuffer& image,
        unsigned int threadCount
    ) override;

    std::string name() const override;

private:
    int x_;
    int y_;
    int width_;
    int height_;
};

} // namespace ip