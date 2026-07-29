#include "../include/matrix.hpp"

double determinant(const Matrix3x3 &matrix) {
    // TODO: Calculate and return the determinant using standard 3x3 co-factor expansion.
    return 0.0;
}

Matrix3x3 inverse(const Matrix3x3 &matrix) {
    // TODO: Compute the inverse using the determinant and adjugate of the matrix.
    return {};
}

Matrix3x3 operator*(const Matrix3x3 &lhs, const Matrix3x3 &rhs) {
    // TODO: Multiply two 3x3 matrices using row-by-column multiplication.
    return {};
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
