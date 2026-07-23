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
    // TODO: Multiply two 4x4 matrices using row-by-column multiplication.
    return {};
}

Matrix3x3 createTranslationMatrix(double tx, double ty) {
    // TODO: Construct a homogeneous translation matrix using horizontal and vertical offsets.
    return {};
}

Matrix3x3 createScaleMatrix(double sx, double sy) {
    // TODO:  Construct a homogeneous scaling matrix using horizontal and vertical factors.
    return {};
}

Matrix3x3 createRotationMatrix(double theta) {
    // TODO: Construct a homogeneous rotation matrix using the supplied radian angle.
    return {};
}

Matrix3x3 createShearMatrix(double alpha, double beta) {
    // TODO: Construct a homogeneous shear matrix using horizontal and vertical shear angles.
    return {};
}

Matrix4x4 createGrayscaleMatrix(double amount) {
    // TODO: Construct a homogeneous shear matrix using horizontal and vertical shear angles.
    return {};
}

Matrix4x4 createSepiaMatrix(double amount) {
    // TODO: Construct a color matrix blending original colors toward sepia tones.
    return {};
}

Matrix4x4 createInvertMatrix(double amount) {
    // TODO: Construct a color matrix blending channels toward their inverted values.
    return {};
}

Matrix4x4 createBrightnessMatrix(double amount) {
    // TODO: Construct a color matrix adjusting RGB brightness by the supplied factor.
    return {};
}

Matrix4x4 createContrastMatrix(double amount) {
    // TODO:  Construct a color matrix adjusting contrast around the channel midpoint.
    return {};
}

Matrix4x4 createSaturateMatrix(double amount) {
    // TODO: Construct a color matrix adjusting saturation while preserving perceived luminance.
    return {};
}
