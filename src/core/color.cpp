#include "../../include/core/color.hpp"

#include <algorithm>
#include <cmath>

ColorVector4 pixelToColor4(const Pixel &p) {
    return ColorVector4{static_cast<double>(p.red), static_cast<double>(p.green), static_cast<double>(p.blue), 1.0};
}

Pixel color4ToPixel(const ColorVector4 &vec) {
    return Pixel{clampColor(vec.b / vec.w), clampColor(vec.g / vec.w), clampColor(vec.r / vec.w)};
}

std::uint8_t clampColor(double value) {
    const double rounded = std::round(value);
    return static_cast<std::uint8_t>(std::clamp(rounded, 0.0, 255.0));
}
