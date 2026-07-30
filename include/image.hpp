#pragma once

#include "bmp24.hpp"
#include "transform.hpp"

/**
 * @brief Returns the pixel at the specified coordinates.
 *
 * If the coordinates are outside the image boundaries, a black pixel is returned.
 *
 * @param img Source image.
 * @param x X-coordinate.
 * @param y Y-coordinate.
 * @return Pixel at the specified position, or a black pixel if out of bounds.
 */
[[nodiscard]]
Pixel getPixelSafe(const BMPImage &img, std::int32_t x, std::int32_t y);

/**
 * @brief Gets the bounding information of a BMP image.
 *
 * The returned bounds describe the image in its local coordinate system,
 * where the top-left pixel is located at (0, 0).
 *
 * @param image The BMP image.
 * @return The bounding information of the image.
 */
[[nodiscard]]
TransformedImageBounds getImageBounds(const BMPImage &image);
