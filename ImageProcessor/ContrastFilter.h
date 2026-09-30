#pragma once

/**
 * @file ContrastFilter.h
 * @brief 이미지 대비 조절 필터.
 */

#include "FilterBase.h"

namespace ip {

class ContrastFilter : public FilterBase {
public:
    explicit ContrastFilter(double factor);

    void apply(
        ImageBuffer& image,
        unsigned int threadCount
    ) override;

    std::string name() const override;

private:
    double factor_;
};

} // namespace ip