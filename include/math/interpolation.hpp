#pragma once

#include "io/bmp24.hpp"

/**
 * @brief Computes a pixel value at a continuous source coordinate
 *        using bilinear interpolation.
 *
 * @param srcImage Source image.
 * @param srcX Continuous horizontal coordinate in the source image.
 * @param srcY Continuous vertical coordinate in the source image.
 * @return The interpolated pixel value.
 */
[[nodiscard]]
Pixel bilinearInterpolate(const BMPImage &srcImage, double srcX, double srcY);
