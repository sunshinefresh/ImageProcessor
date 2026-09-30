#pragma once

/**
 * @file GrayscaleFilter.h
 */

#include "FilterBase.h"

namespace ip {

class GrayscaleFilter : public FilterBase {
public:
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
};

} // namespace ip