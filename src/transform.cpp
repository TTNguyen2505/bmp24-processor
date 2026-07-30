#include "../include/transform.hpp"

#include <algorithm>
#include <cmath>
#include <utility>

#include "../include/util.hpp"

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

TransformedImageBounds calculateNewDimensions(const TransformedImageBounds &bounds, const Matrix3x3 &T) {

    const double left = static_cast<double>(bounds.minX);
    const double top = static_cast<double>(bounds.minY);

    const double right = left + bounds.width - 1.0;
    const double bottom = top + bounds.height - 1.0;

    const CoordinateVector3 corners[4] = {T * CoordinateVector3{left, top, 1.0}, T * CoordinateVector3{right, top, 1.0},
                                          T * CoordinateVector3{left, bottom, 1.0},
                                          T * CoordinateVector3{right, bottom, 1.0}};

    double minX = corners[0].x;
    double maxX = corners[0].x;
    double minY = corners[0].y;
    double maxY = corners[0].y;

    for (std::size_t i = 1; i < 4; ++i) {
        minX = std::min(minX, corners[i].x);
        maxX = std::max(maxX, corners[i].x);

        minY = std::min(minY, corners[i].y);
        maxY = std::max(maxY, corners[i].y);
    }

    const std::int32_t newMinX = static_cast<std::int32_t>(std::floor(minX));

    const std::int32_t newMinY = static_cast<std::int32_t>(std::floor(minY));

    const std::int32_t newWidth = static_cast<std::int32_t>(std::ceil(maxX)) - newMinX + 1;

    const std::int32_t newHeight = static_cast<std::int32_t>(std::ceil(maxY)) - newMinY + 1;

    return {newWidth, newHeight, newMinX, newMinY};
}

Pixel bilinearInterpolate(const BMPImage &srcImage, double srcX, double srcY) {
    const std::int32_t x0 = static_cast<std::int32_t>(std::floor(srcX));
    const std::int32_t y0 = static_cast<std::int32_t>(std::floor(srcY));

    // Outside the source image
    if (x0 < 0 || x0 >= getWidth(srcImage) || y0 < 0 || y0 >= getHeight(srcImage)) {
        return Pixel{0, 0, 0};
    }

    const double dx = srcX - x0;
    const double dy = srcY - y0;

    // Bottom-right corner
    if (x0 == getWidth(srcImage) - 1 && y0 == getHeight(srcImage) - 1) {
        return getPixelSafe(srcImage, x0, y0);
    }

    // Right border
    if (x0 == getWidth(srcImage) - 1) {
        const Pixel p0 = getPixelSafe(srcImage, x0, y0);
        const Pixel p1 = getPixelSafe(srcImage, x0, y0 + 1);

        return Pixel{clampColor((1.0 - dy) * p0.red + dy * p1.red), clampColor((1.0 - dy) * p0.green + dy * p1.green),
                     clampColor((1.0 - dy) * p0.blue + dy * p1.blue)};
    }

    // Bottom border
    if (y0 == getHeight(srcImage) - 1) {
        const Pixel p0 = getPixelSafe(srcImage, x0, y0);
        const Pixel p1 = getPixelSafe(srcImage, x0 + 1, y0);

        return Pixel{clampColor((1.0 - dx) * p0.red + dx * p1.red), clampColor((1.0 - dx) * p0.green + dx * p1.green),
                     clampColor((1.0 - dx) * p0.blue + dx * p1.blue)};
    }

    // Bilinear interpolation
    const Pixel p00 = getPixelSafe(srcImage, x0, y0);
    const Pixel p10 = getPixelSafe(srcImage, x0 + 1, y0);
    const Pixel p01 = getPixelSafe(srcImage, x0, y0 + 1);
    const Pixel p11 = getPixelSafe(srcImage, x0 + 1, y0 + 1);

    const double w00 = (1.0 - dx) * (1.0 - dy);
    const double w10 = dx * (1.0 - dy);
    const double w01 = (1.0 - dx) * dy;
    const double w11 = dx * dy;

    return Pixel{clampColor(w00 * p00.red + w10 * p10.red + w01 * p01.red + w11 * p11.red),
                 clampColor(w00 * p00.green + w10 * p10.green + w01 * p01.green + w11 * p11.green),
                 clampColor(w00 * p00.blue + w10 * p10.blue + w01 * p01.blue + w11 * p11.blue)};
    return {};
}

BMPImage applyTransformMatrix(const BMPImage &srcImage, const Matrix3x3 &T) {
    const TransformedImageBounds bounds = calculateNewDimensions(getImageBounds(srcImage), T);

    BMPImage dstImage = srcImage;

    // Update dimensions
    setWidth(dstImage, bounds.width);
    setHeight(dstImage, bounds.height);

    // Allocate destination pixels
    dstImage.data.assign(static_cast<std::size_t>(bounds.width) * bounds.height, Pixel{0, 0, 0});

    // Update image size
    const std::size_t rowSize = static_cast<std::size_t>(bounds.width) * 3 + calculatePadding(bounds.width);

    const std::uint32_t imageSize = static_cast<std::uint32_t>(rowSize * static_cast<std::size_t>(bounds.height));

    setImageSize(dstImage, imageSize);

    dstImage.fileHeader.size = dstImage.fileHeader.offset + imageSize;

    // Inverse mapping
    const Matrix3x3 inverseT = inverse(T);

    for (std::int32_t y = 0; y < bounds.height; ++y) {
        for (std::int32_t x = 0; x < bounds.width; ++x) {

            CoordinateVector3 dstCoord{static_cast<double>(x + bounds.minX), static_cast<double>(y + bounds.minY), 1.0};

            CoordinateVector3 srcCoord = inverseT * dstCoord;

            // Normalize homogeneous coordinate (future-proof)
            if (srcCoord.w != 0.0) {
                srcCoord.x /= srcCoord.w;
                srcCoord.y /= srcCoord.w;
            }

            dstImage.data[static_cast<std::size_t>(y) * bounds.width + x] =
                    bilinearInterpolate(srcImage, srcCoord.x, srcCoord.y);
        }
    }

    return dstImage;
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


/**
 * @brief Creates a transformation matrix about the center of an image.
 *
 * The transformation is constructed as:
 *      T(center) * M * T(-center)
 * where M is the transformation matrix defined about the origin.
 *
 * @param transform Transformation matrix about the origin.
 * @param bounds Bounding information of the current image.
 * @return A transformation matrix about the image center.
 */
[[nodiscard]]
Matrix3x3 createCenteredTransform(const Matrix3x3 &transform, const TransformedImageBounds &bounds) {
    const double centerX = bounds.minX + (bounds.width - 1) / 2.0;
    const double centerY = bounds.minY + (bounds.height - 1) / 2.0;

    return createTranslationMatrix(centerX, centerY) * transform * createTranslationMatrix(-centerX, -centerY);
}

Matrix3x3 createRotationCenterMatrix(double angle, const TransformedImageBounds &bounds) {
    return createCenteredTransform(createRotationMatrix(angle), bounds);
}

Matrix3x3 createScaleCenterMatrix(double scaleX, double scaleY, const TransformedImageBounds &bounds) {
    return createCenteredTransform(createScaleMatrix(scaleX, scaleY), bounds);
}

Matrix3x3 createShearCenterMatrix(double shearX, double shearY, const TransformedImageBounds &bounds) {
    return createCenteredTransform(createShearMatrix(shearX, shearY), bounds);
}
