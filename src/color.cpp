#include "../include/color.hpp"

#include <algorithm>

ColorVector4 pixelToColor4(const Pixel &p) {
    return ColorVector4{static_cast<double>(p.red), static_cast<double>(p.green), static_cast<double>(p.blue), 1.0};
}

std::uint8_t doubleToByte(double value) {
    double clamped = std::clamp(value, 0.0, 255.0);
    return static_cast<std::uint8_t>(clamped + 0.5);
}

Pixel color4ToPixel(const ColorVector4 &c) { return Pixel{doubleToByte(c.b), doubleToByte(c.r), doubleToByte(c.r)}; }
