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
    // Grayscale transformation using luminance weights: 0.299R + 0.587G + 0.114B
    // Blends from identity (amount=0) to pure grayscale (amount=1)
    Matrix4x4 gray;
    const double r = 0.299;
    const double g = 0.587;
    const double b = 0.114;

    gray.data[0][0] = 1.0 - amount + r * amount;
    gray.data[0][1] = g * amount;
    gray.data[0][2] = b * amount;

    gray.data[1][0] = r * amount;
    gray.data[1][1] = 1.0 - amount + g * amount;
    gray.data[1][2] = b * amount;

    gray.data[2][0] = r * amount;
    gray.data[2][1] = g * amount;
    gray.data[2][2] = 1.0 - amount + b * amount;

    gray.data[3][3] = 1.0;
    return gray;
}

Matrix4x4 createSepiaMatrix(double amount) {
    // Sepia tone transformation using standard sepia matrix coefficients
    // Blends from identity (amount=0) to full sepia (amount=1)
    Matrix4x4 sepia;
    const double sr = 0.393;
    const double sg = 0.769;
    const double sb = 0.189;

    const double gr = 0.349;
    const double gg = 0.686;
    const double gb = 0.168;

    const double br = 0.272;
    const double bg = 0.534;
    const double bb = 0.131;

    sepia.data[0][0] = 1.0 - amount + sr * amount;
    sepia.data[0][1] = sg * amount;
    sepia.data[0][2] = sb * amount;

    sepia.data[1][0] = gr * amount;
    sepia.data[1][1] = 1.0 - amount + gg * amount;
    sepia.data[1][2] = gb * amount;

    sepia.data[2][0] = br * amount;
    sepia.data[2][1] = bg * amount;
    sepia.data[2][2] = 1.0 - amount + bb * amount;

    sepia.data[3][3] = 1.0;
    return sepia;
}

Matrix4x4 createInvertMatrix(double amount) {
    // Color inversion: RGB -> (255-R, 255-G, 255-B)
    // Blends from identity (amount=0) to full inversion (amount=1)
    Matrix4x4 invert;

    invert.data[0][0] = 1.0 - amount;
    invert.data[0][3] = 255.0 * amount;

    invert.data[1][1] = 1.0 - amount;
    invert.data[1][3] = 255.0 * amount;

    invert.data[2][2] = 1.0 - amount;
    invert.data[2][3] = 255.0 * amount;

    invert.data[3][3] = 1.0;
    return invert;
}

Matrix4x4 createBrightnessMatrix(double amount) {
    // Brightness adjustment: scales RGB channels uniformly
    // amount < 1.0 darkens, amount > 1.0 brightens
    Matrix4x4 brightness;

    brightness.data[0][0] = amount;
    brightness.data[1][1] = amount;
    brightness.data[2][2] = amount;
    brightness.data[3][3] = 1.0;

    return brightness;
}

Matrix4x4 createContrastMatrix(double amount) {
    // Contrast adjustment: scales channels around midpoint (127.5)
    // Centers at 127.5, scales by amount, then re-centers
    Matrix4x4 contrast;
    const double offset = (1.0 - amount) * 127.5;

    contrast.data[0][0] = amount;
    contrast.data[0][3] = offset;

    contrast.data[1][1] = amount;
    contrast.data[1][3] = offset;

    contrast.data[2][2] = amount;
    contrast.data[2][3] = offset;

    contrast.data[3][3] = 1.0;
    return contrast;
}

Matrix4x4 createSaturateMatrix(double amount) {
    // Saturation adjustment: adjusts distance from grayscale
    // Uses luminance weights to preserve perceived brightness
    Matrix4x4 saturate;
    const double lum_r = 0.299;
    const double lum_g = 0.587;
    const double lum_b = 0.114;

    saturate.data[0][0] = lum_r * (1.0 - amount) + amount;
    saturate.data[0][1] = lum_g * (1.0 - amount);
    saturate.data[0][2] = lum_b * (1.0 - amount);

    saturate.data[1][0] = lum_r * (1.0 - amount);
    saturate.data[1][1] = lum_g * (1.0 - amount) + amount;
    saturate.data[1][2] = lum_b * (1.0 - amount);

    saturate.data[2][0] = lum_r * (1.0 - amount);
    saturate.data[2][1] = lum_g * (1.0 - amount);
    saturate.data[2][2] = lum_b * (1.0 - amount) + amount;

    saturate.data[3][3] = 1.0;
    return saturate;
}
