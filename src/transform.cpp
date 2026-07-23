#include "../include/transform.hpp"

std::pair<int, int> calculateNewDimensions(int srcWidth, int srcHeight, const Matrix3x3 &T) {
    // TODO: Transform image corners and calculate the resulting axis-aligned bounding dimensions.
}

Pixel bilinearInterpolate(const BMPImage &srcImage, double srcX, double srcY) {
    // TODO: Interpolate neighboring pixels safely, handling boundaries and clamping channel values.
}

BMPImage applyTransformMatrix(const BMPImage &srcImage, const Matrix3x3 &T) {
    // TODO: Create destination image, inverse-map pixels, interpolate colors, and preserve metadata.
}

bool applyTranslation(BMPImage &img, double tx, double ty) {
    // TODO: Validate parameters, apply the translation matrix, and report transformation success.
}

bool applyScale(BMPImage &img, double sx, double sy) {
    // TODO: Validate scale factors, apply the scaling matrix, and report transformation success.
}

bool applyRotation(BMPImage &img, double theta) {
    // TODO: 
}

bool applyShear(BMPImage &img, double alpha, double beta) {
    // TODO: Validate parameters, apply the shear matrix, and report transformation success.
}
