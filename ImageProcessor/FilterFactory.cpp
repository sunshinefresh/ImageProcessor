#include "FilterFactory.h"

#include "BrightnessFilter.h"
#include "ContrastFilter.h"
#include "ConvolutionFilter.h"
#include "CropFilter.h"
#include "Exceptions.h"
#include "FlipFilter.h"
#include "GrayscaleFilter.h"
#include "HistogramFilter.h"
#include "ResizeFilter.h"
#include "ThresholdFilter.h"

#include <sstream>

namespace ip {

std::unique_ptr<FilterBase> FilterFactory::create(
    const std::string& filterName
) {
    if (filterName == "grayscale") {
        return std::make_unique<GrayscaleFilter>();
    }

    if (filterName.rfind("brightness:", 0) == 0) {
        const std::string valueText =
            filterName.substr(
                std::string("brightness:").length()
            );

        const int amount = std::stoi(valueText);

        if (amount < -255 || amount > 255) {
            throw FilterError(
                "Brightness must be between -255 and 255"
            );
        }

        return std::make_unique<BrightnessFilter>(amount);
    }

    if (filterName.rfind("contrast:", 0) == 0) {
        const std::string valueText =
            filterName.substr(
                std::string("contrast:").length()
            );

        const double factor = std::stod(valueText);

        if (factor < 0.0) {
            throw FilterError(
                "Contrast must be 0 or greater"
            );
        }

        return std::make_unique<ContrastFilter>(factor);
    }

    if (filterName.rfind("threshold:", 0) == 0) {
        const std::string valueText =
            filterName.substr(
                std::string("threshold:").length()
            );

        const int threshold = std::stoi(valueText);

        if (threshold < 0 || threshold > 255) {
            throw FilterError(
                "Threshold must be between 0 and 255"
            );
        }

        return std::make_unique<ThresholdFilter>(
            static_cast<std::uint8_t>(threshold)
        );
    }

    if (filterName == "blur") {
        return std::make_unique<ConvolutionFilter>(
            ConvolutionType::Blur
        );
    }

    if (filterName == "sharpen") {
        return std::make_unique<ConvolutionFilter>(
            ConvolutionType::Sharpen
        );
    }

    if (filterName == "histogram") {
        return std::make_unique<HistogramFilter>();
    }

    if (filterName.rfind("crop:", 0) == 0) {
        const std::string values =
            filterName.substr(
                std::string("crop:").length()
            );

        std::stringstream stream(values);

        int x = 0;
        int y = 0;
        int width = 0;
        int height = 0;

        char comma1 = '\0';
        char comma2 = '\0';
        char comma3 = '\0';

        if (
            !(stream >> x >> comma1 >> y >> comma2 >> width >> comma3 >> height) ||
            comma1 != ',' ||
            comma2 != ',' ||
            comma3 != ','
            ) {
            throw FilterError(
                "Crop format: crop:x,y,width,height"
            );
        }

        return std::make_unique<CropFilter>(
            x,
            y,
            width,
            height
        );
    }

    if (filterName.rfind("resize:", 0) == 0) {
        const std::string values =
            filterName.substr(
                std::string("resize:").length()
            );

        std::stringstream stream(values);

        int width = 0;
        int height = 0;
        char comma = '\0';

        if (
            !(stream >> width >> comma >> height) ||
            comma != ','
            ) {
            throw FilterError(
                "Resize format: resize:width,height"
            );
        }

        return std::make_unique<ResizeFilter>(
            width,
            height
        );
    }

    if (filterName == "flip:horizontal") {
        return std::make_unique<FlipFilter>(
            FlipDirection::Horizontal
        );
    }

    if (filterName == "flip:vertical") {
        return std::make_unique<FlipFilter>(
            FlipDirection::Vertical
        );
    }

    throw FilterError(
        "Filter does not exist: " + filterName
    );
}

} // namespace ip