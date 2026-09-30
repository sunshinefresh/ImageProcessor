#pragma once

/**
 * @file FlipFilter.h.
 */

#include "FilterBase.h"

namespace ip {

enum class FlipDirection {
    Horizontal,
    Vertical
};

class FlipFilter : public FilterBase {
public:
    explicit FlipFilter(FlipDirection direction);

    void apply(
        ImageBuffer& image,
        unsigned int threadCount
    ) override;

    std::string name() const override;

private:
    FlipDirection direction_;
};

} // namespace ip