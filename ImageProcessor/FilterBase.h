#pragma once

/**
 * @file FilterBase.h
 */

#include "ImageBuffer.h"

#include <string>

namespace ip {

    class FilterBase {
    public:
        virtual ~FilterBase() = default;

        virtual void apply(
            ImageBuffer& image,
            unsigned int threadCount
        ) = 0;

        virtual std::string name() const = 0;
    };

} // namespace ip