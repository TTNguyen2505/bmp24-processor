#include "../../include/math/matrix.hpp"

#include <cmath>
#include <stdexcept>

double determinant(const Matrix3x3 &matrix) {
    const auto &m = matrix.data;

    return m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) - m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
           m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
}

Matrix3x3 inverse(const Matrix3x3 &matrix) {
    const double det = determinant(matrix);

    if (std::abs(det) < 1e-12) {
        throw std::runtime_error("Matrix is singular and cannot be inverted.");
    }

    const auto &m = matrix.data;

    Matrix3x3 inv{};

    inv.data[0][0] = (m[1][1] * m[2][2] - m[1][2] * m[2][1]) / det;
    inv.data[0][1] = (m[0][2] * m[2][1] - m[0][1] * m[2][2]) / det;
    inv.data[0][2] = (m[0][1] * m[1][2] - m[0][2] * m[1][1]) / det;

    inv.data[1][0] = (m[1][2] * m[2][0] - m[1][0] * m[2][2]) / det;
    inv.data[1][1] = (m[0][0] * m[2][2] - m[0][2] * m[2][0]) / det;
    inv.data[1][2] = (m[0][2] * m[1][0] - m[0][0] * m[1][2]) / det;

    inv.data[2][0] = (m[1][0] * m[2][1] - m[1][1] * m[2][0]) / det;
    inv.data[2][1] = (m[0][1] * m[2][0] - m[0][0] * m[2][1]) / det;
    inv.data[2][2] = (m[0][0] * m[1][1] - m[0][1] * m[1][0]) / det;

    return inv;
}

Matrix3x3 operator*(const Matrix3x3 &lhs, const Matrix3x3 &rhs) {
    Matrix3x3 result{};

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            result.data[row][col] = 0.0;

            for (int k = 0; k < 3; ++k) {
                result.data[row][col] += lhs.data[row][k] * rhs.data[k][col];
            }
        }
    }

    return result;
}

Matrix4x4 operator*(const Matrix4x4 &lhs, const Matrix4x4 &rhs) {
    // Multiply two 4x4 matrices: result[i][j] = sum(lhs[i][k] * rhs[k][j])
    Matrix4x4 result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.data[i][j] = 0.0;
            for (int k = 0; k < 4; ++k) {
                result.data[i][j] += lhs.data[i][k] * rhs.data[k][j];
            }
        }
    }
    return result;
}

CoordinateVector3 operator*(const Matrix3x3 &mat, const CoordinateVector3 &vec) {
    CoordinateVector3 result;

    result.x = mat.data[0][0] * vec.x + mat.data[0][1] * vec.y + mat.data[0][2] * vec.w;
    result.y = mat.data[1][0] * vec.x + mat.data[1][1] * vec.y + mat.data[1][2] * vec.w;
    result.w = mat.data[2][0] * vec.x + mat.data[2][1] * vec.y + mat.data[2][2] * vec.w;

    return result;
}

ColorVector4 operator*(const Matrix4x4 &mat, const ColorVector4 &vec) {
    ColorVector4 result;
    result.r = mat.data[0][0] * vec.r + mat.data[0][1] * vec.g + mat.data[0][2] * vec.b + mat.data[0][3] * vec.w;
    result.g = mat.data[1][0] * vec.r + mat.data[1][1] * vec.g + mat.data[1][2] * vec.b + mat.data[1][3] * vec.w;
    result.b = mat.data[2][0] * vec.r + mat.data[2][1] * vec.g + mat.data[2][2] * vec.b + mat.data[2][3] * vec.w;
    result.w = mat.data[3][0] * vec.r + mat.data[3][1] * vec.g + mat.data[3][2] * vec.b + mat.data[3][3] * vec.w;

    return result;
}
