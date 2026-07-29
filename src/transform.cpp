#include "../include/transform.hpp"

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
