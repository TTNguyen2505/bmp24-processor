#include "../include/transform.hpp"

#include <cmath>

constexpr double PI = 3.14159265358979323846;

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
double degToRad(double degree) {
    return degree * PI / 180.0;
}

std::pair<int, int> calculateNewDimensions(int srcWidth, int srcHeight, const Matrix3x3 &T) {
    // TODO: Transform image corners and calculate the resulting axis-aligned bounding dimensions.
    return {};
}

Pixel bilinearInterpolate(const BMPImage &srcImage, double srcX, double srcY) {
    // TODO: Interpolate neighboring pixels safely, handling boundaries and clamping channel values.
    return {};
}

BMPImage applyTransformMatrix(const BMPImage &srcImage, const Matrix3x3 &T) {
    // TODO: Create destination image, inverse-map pixels, interpolate colors, and preserve metadata.
    return {};
}

Matrix3x3 createTranslationMatrix(double tx, double ty) {
    Matrix3x3 mat{};

    mat.data[0][0] = 1.0;
    mat.data[0][1] = 0.0;
    mat.data[0][2] = tx;

    mat.data[1][0] = 0.0;
    mat.data[1][1] = 1.0;
    mat.data[1][2] = ty;

    mat.data[2][0] = 0.0;
    mat.data[2][1] = 0.0;
    mat.data[2][2] = 1.0;

    return mat;
}

Matrix3x3 createScaleMatrix(double sx, double sy) {
    Matrix3x3 mat{};

    mat.data[0][0] = sx;
    mat.data[0][1] = 0.0;
    mat.data[0][2] = 0.0;

    mat.data[1][0] = 0.0;
    mat.data[1][1] = sy;
    mat.data[1][2] = 0.0;

    mat.data[2][0] = 0.0;
    mat.data[2][1] = 0.0;
    mat.data[2][2] = 1.0;

    return mat;
}

Matrix3x3 createRotationMatrix(double theta) {
    const double radians = degToRad(theta);
    const double c = std::cos(radians);
    const double s = std::sin(radians);

    Matrix3x3 mat{};

    mat.data[0][0] = c;
    mat.data[0][1] = -s;
    mat.data[0][2] = 0.0;

    mat.data[1][0] = s;
    mat.data[1][1] = c;
    mat.data[1][2] = 0.0;

    mat.data[2][0] = 0.0;
    mat.data[2][1] = 0.0;
    mat.data[2][2] = 1.0;

    return mat;
}

Matrix3x3 createShearMatrix(double alpha, double beta) {
    const double alphaRad = degToRad(alpha);
    const double betaRad = degToRad(beta);

    Matrix3x3 mat{};

    mat.data[0][0] = 1.0;
    mat.data[0][1] = std::tan(alphaRad);
    mat.data[0][2] = 0.0;

    mat.data[1][0] = std::tan(betaRad);
    mat.data[1][1] = 1.0;
    mat.data[1][2] = 0.0;

    mat.data[2][0] = 0.0;
    mat.data[2][1] = 0.0;
    mat.data[2][2] = 1.0;

    return mat;
}
