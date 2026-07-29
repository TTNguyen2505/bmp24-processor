#pragma once

#include <tuple>
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

/**
 * @brief Converts a homogeneous coordinate vector back to a 2D point.
 *
 * If the homogeneous coordinate is not equal to 1.0, the coordinates are
 * normalized by dividing x and y by w.
 *
 * @param point Input homogeneous coordinate vector.
 * @return std::pair<double, double> The resulting Cartesian coordinates.
 */
[[nodiscard]]
std::pair<double, double> coordinate3ToPoint(const CoordinateVector3 &point);