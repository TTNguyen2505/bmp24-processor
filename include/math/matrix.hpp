#pragma once

#include "../core/color.hpp"
#include "../math/coordinate.hpp"

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
 * @brief Multiplies a 4x4 color transformation matrix by a 4D homogeneous color vector.
 *
 * Applies a color transformation (such as grayscale, sepia, brightness,
 * contrast, saturation, or color mixing) to a color vector
 * [r, g, b, w]^T.
 *
 * @param mat The 4x4 color transformation matrix.
 * @param vec The 4D homogeneous color vector.
 * @return ColorVector4 The transformed color vector.
 */
[[nodiscard]]
ColorVector4 operator*(const Matrix4x4 &mat, const ColorVector4 &vec);

/**
 * @brief Creates an identity transformation matrix for a given Matrix type.
 *
 * @tparam T The matrix type (e.g., Matrix3x3, Matrix4x4).
 * @return T An identity matrix of type T.
 */
template<typename T>
[[nodiscard]] constexpr T createIdentityMatrix() {
    T mat{};
    constexpr std::size_t N = sizeof(mat.data) / sizeof(mat.data[0]);

    for (std::size_t i = 0; i < N; ++i) {
        mat.data[i][i] = 1.0;
    }
    return mat;
}
