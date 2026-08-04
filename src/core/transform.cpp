#include "../../include/core/transform.hpp"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <utility>

#include "../../include/core/color.hpp"
#include "../../include/core/image.hpp"
#include "../../include/io/bmp_io.hpp"
#include "../../include/math/geometry.hpp"
#include "../../include/math/interpolation.hpp"

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
    return Matrix3x3{{{1.0, 0.0, tx}, {0.0, 1.0, ty}, {0.0, 0.0, 1.0}}};
}

Matrix3x3 createScaleMatrix(double sx, double sy) {
    return Matrix3x3{{{sx, 0.0, 0.0}, {0.0, sy, 0.0}, {0.0, 0.0, 1.0}}};
}

Matrix3x3 createRotationMatrix(double theta) {
    const double rad = degToRad(theta);
    const double c = std::cos(rad);
    const double s = std::sin(rad);

    return Matrix3x3{{{c, -s, 0.0}, {s, c, 0.0}, {0.0, 0.0, 1.0}}};
}

Matrix3x3 createShearMatrix(double alpha, double beta) {
    const double tanAlpha = std::tan(degToRad(alpha));
    const double tanBeta = std::tan(degToRad(beta));

    return Matrix3x3{{{1.0, tanAlpha, 0.0}, {tanBeta, 1.0, 0.0}, {0.0, 0.0, 1.0}}};
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
