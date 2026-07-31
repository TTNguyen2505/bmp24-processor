#include "../../include/core/color.hpp"

#include <algorithm>
#include <cmath>

ColorVector4 pixelToColor4(const Pixel &p) {
    return ColorVector4{static_cast<double>(p.red), static_cast<double>(p.green), static_cast<double>(p.blue), 1.0};
}

std::uint8_t doubleToByte(double value) {
    const double clamped = std::clamp(value, 0.0, 255.0);
    return static_cast<std::uint8_t>(clamped + 0.5);
}

Pixel color4ToPixel(const ColorVector4 &c) { return Pixel{doubleToByte(c.b), doubleToByte(c.r), doubleToByte(c.r)}; }

std::uint8_t clampColor(double value) {
    const double rounded = std::round(value);
    return static_cast<std::uint8_t>(std::clamp(rounded, 0.0, 255.0));
}
