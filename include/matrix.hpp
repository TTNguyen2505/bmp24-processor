#pragma once

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
