#pragma once

#include <cstdint>

#include "bmp24.hpp"

struct ColorVector4 {
    double r{0.0}; /**< Red color component in range [0.0, 255.0] */
    double g{0.0}; /** Green color component in range [0.0, 255.0] */
    double b{0.0}; /** Blue color component in range [0.0, 255.0] */
    double w{1.0}; /**< Homogeneous coordinate (always 1.0 for affine color matrix transformation) */
};

/**
 * @brief Converts a 24-bit BMP Pixel (8-bit per channel) to a ColorVector4 double vector.
 *
 * @param p The input Pixel containing integral BGR color values in [0, 255].
 * @return ColorVector4 A 4D double color vector with w = 1.0.
 */
[[nodiscard]]
ColorVector4 pixelToColor4(const Pixel &p);

/**
 * @brief Clamps a double-precision color value to [0.0, 255.0] and converts it to uint8_t.
 *
 * @param value The double color value to be clamped and rounded.
 * @return std::uint8_t The resulting 8-bit unsigned integer color byte.
 */
[[nodiscard]]
std::uint8_t doubleToByte(double value);

/**
 * @brief Converts a ColorVector4 double vector back to a 24-bit BMP Pixel.
 *
 * @param c The input ColorVector4 vector containing calculated double color values.
 * @return Pixel The output Pixel ready to be written to a 24-bit BMP file.
 */
[[nodiscard]]
Pixel color4ToPixel(const ColorVector4 &c);

/**
 * @brief Clamps a color value to the valid 8-bit range [0, 255].
 *
 * @param value Input color value.
 * @return Clamped color value.
 */
[[nodiscard]]
std::uint8_t clampColor(double value);