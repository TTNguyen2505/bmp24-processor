#pragma once

#include <cstdint>

#include "matrix.hpp"

/**
 * @brief Converts an angle from degrees to radians.
 *
 * Calculates the equivalent angle in radians using the formula: rad = deg * PI / 180.
 * Essential for standard trigonometric functions (sin, cos, tan) in transformation matrix calculations.
 *
 * @param degree The angle value measured in degrees.
 * @return double The equivalent angle value measured in radians.
 */
[[nodiscard]]
double degToRad(double degree);

/**
 * @struct TransformedImageBounds
 * @brief Stores the bounding box information of an image after applying a transformation.
 */
struct TransformedImageBounds {
    std::int32_t width{0}; /**< Width of the transformed image in pixels. */
    std::int32_t height{0}; /**< Height of the transformed image in pixels. */
    std::int32_t minX{0}; /**< Minimum X-coordinate of the transformed image. */
    std::int32_t minY{0}; /**< Minimum Y-coordinate of the transformed image. */
};

/**
 * @brief Computes the bounding box of an image after applying a transformation.
 *
 * Transforms the four corners of the current image bounds using the specified
 * transformation matrix and returns the smallest axis-aligned bounding box that
 * contains the transformed image.
 *
 * @param bounds Bounding information of the current image.
 * @param T 3×3 homogeneous transformation matrix.
 * @return Bounding information of the transformed image.
 */
[[nodiscard]]
TransformedImageBounds calculateNewDimensions(const TransformedImageBounds &bounds, const Matrix3x3 &T);
