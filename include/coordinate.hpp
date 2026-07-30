#pragma once


/**
 * @struct CoordinateVector3
 * @brief Represents a 2D point in homogeneous coordinates.
 */
struct CoordinateVector3 {
    double x{0.0}; /**< X-coordinate. */
    double y{0.0}; /**< Y-coordinate. */
    double w{1.0}; /**< Homogeneous coordinate (always 1.0 for affine transformations). */
};

/**
 * @brief Creates a homogeneous coordinate vector from a 2D point.
 *
 * @param x X-coordinate.
 * @param y Y-coordinate.
 * @return CoordinateVector3 A homogeneous coordinate vector with w = 1.0.
 */
[[nodiscard]]
CoordinateVector3 pointToCoordinate3(double x, double y);
