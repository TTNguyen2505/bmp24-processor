#pragma once

#include "math/coordinate.hpp"

/**
 * @struct Matrix3x3
 * @brief Represents a 3×3 matrix for geometric transformations.
 */
struct Matrix3x3 {
    double data[3][3]{{0.0}};
};

/**
 * @struct Matrix4x4
 * @brief Represents a 4×4 matrix for color transformations.
 */
struct Matrix4x4 {
    double data[4][4]{{0.0}};
};

/**
 * @brief Computes the determinant of a 3×3 matrix.
 * @param matrix Input matrix.
 * @return The determinant value.
 */
[[nodiscard]]
double determinant(const Matrix3x3 &matrix);

/**
 * @brief Computes the inverse of a 3×3 matrix.
 * @param matrix Input matrix.
 * @return The inverse matrix.
 */
[[nodiscard]]
Matrix3x3 inverse(const Matrix3x3 &matrix);

/**
 * @brief Multiplies two 3×3 matrices.
 * @param lhs Left-hand matrix.
 * @param rhs Right-hand matrix.
 * @return The resulting matrix.
 */
[[nodiscard]]
Matrix3x3 operator*(const Matrix3x3 &lhs, const Matrix3x3 &rhs);

/**
 * @brief Multiplies two 4×4 matrices.
 * @param lhs Left-hand matrix.
 * @param rhs Right-hand matrix.
 * @return The resulting matrix.
 */
[[nodiscard]]
Matrix4x4 operator*(const Matrix4x4 &lhs, const Matrix4x4 &rhs);

/**
 * @brief Multiplies a 3x3 transformation matrix by a 3D homogeneous coordinate vector.
 *
 * Applies geometric transformations (translation, scaling, rotation, shearing)
 * to a pixel coordinate vector [x, y, w]^T.
 *
 * @param mat The 3x3 transformation matrix.
 * @param vec The 3D coordinate vector.
 * @return CoordinateVector3 The transformed coordinate vector.
 */
[[nodiscard]]
CoordinateVector3 operator*(const Matrix3x3 &mat, const CoordinateVector3 &vec);

/**
 * @brief Creates a 3×3 identity transformation matrix.
 *
 * The identity matrix represents a transformation that leaves all points
 * unchanged. It is commonly used as the starting point when composing
 * multiple affine transformations.
 *
 * @return A 3×3 identity matrix.
 */
[[nodiscard]]
Matrix3x3 createIdentityMatrix();
