#pragma once

#include "bmp24.hpp"
#include "matrix.hpp"

/**
 * @struct TransformedImageBounds
 * @brief Stores the bounding box information of an image after applying a transformation.
 */
struct TransformedImageBounds {
    std::int32_t width{0}; /**< Width of the transformed image in pixels. */
    std::int32_t height{0}; /**< Height of the transformed image in pixels. */
    std::int32_t minX{0}; /**< Minimum X-coordinate of the transformed image. */
    std::int32_t minY{0}; /**< Minimum Y-coordinate of the transformed image. */
};

/**
 * @brief Computes the bounding box of an image after applying a transformation.
 *
 * Transforms the four corners of the current image bounds using the specified
 * transformation matrix and returns the smallest axis-aligned bounding box that
 * contains the transformed image.
 *
 * @param bounds Bounding information of the current image.
 * @param T 3×3 homogeneous transformation matrix.
 * @return Bounding information of the transformed image.
 */
[[nodiscard]]
TransformedImageBounds calculateNewDimensions(const TransformedImageBounds &bounds, const Matrix3x3 &T);

/**
 * @brief Computes a pixel value at a continuous source coordinate
 *        using bilinear interpolation.
 *
 * @param srcImage Source image.
 * @param srcX Continuous horizontal coordinate in the source image.
 * @param srcY Continuous vertical coordinate in the source image.
 * @return The interpolated pixel value.
 */
[[nodiscard]]
Pixel bilinearInterpolate(const BMPImage &srcImage, double srcX, double srcY);

/**
 * @brief Applies a transformation matrix to an image.
 * @param srcImage Source image.
 * @param T 3×3 transformation matrix.
 * @return The transformed image.
 */
[[nodiscard]]
BMPImage applyTransformMatrix(const BMPImage &srcImage, const Matrix3x3 &T);

/**
 * @brief Creates a translation matrix.
 * @param tx Translation along the x-axis.
 * @param ty Translation along the y-axis.
 * @return A translation matrix.
 */
[[nodiscard]]
Matrix3x3 createTranslationMatrix(double tx, double ty);

/**
 * @brief Creates a scaling matrix.
 * @param sx Scale factor along the x-axis.
 * @param sy Scale factor along the y-axis.
 * @return A scaling matrix.
 */
[[nodiscard]]
Matrix3x3 createScaleMatrix(double sx, double sy);

/**
 * @brief Creates a rotation matrix.
 * @param theta Rotation angle in radians.
 * @return A rotation matrix.
 */
[[nodiscard]]
Matrix3x3 createRotationMatrix(double theta);

/**
 * @brief Creates a shear matrix.
 * @param alpha Shear angle along the x-axis.
 * @param beta Shear angle along the y-axis.
 * @return A shear matrix.
 */
[[nodiscard]]
Matrix3x3 createShearMatrix(double alpha, double beta);

/**
 * @brief Creates a rotation matrix about the center of an image.
 *
 * The resulting transformation first translates the image center to the origin,
 * applies the rotation, and then translates the image back to its original position.
 *
 * @param angle Rotation angle in degrees.
 * @param bounds Bounding information of the current image.
 * @return A 3×3 homogeneous transformation matrix representing the rotation
 *         about the image center.
 */
[[nodiscard]]
Matrix3x3 createRotationCenterMatrix(double angle, const TransformedImageBounds &bounds);

/**
 * @brief Creates a scaling matrix about the center of an image.
 *
 * The resulting transformation first translates the image center to the origin,
 * applies the scaling operation, and then translates the image back to its
 * original position.
 *
 * @param scaleX Scaling factor along the X-axis.
 * @param scaleY Scaling factor along the Y-axis.
 * @param bounds Bounding information of the current image.
 * @return A 3×3 homogeneous transformation matrix representing the scaling
 *         about the image center.
 */
[[nodiscard]]
Matrix3x3 createScaleCenterMatrix(double scaleX, double scaleY, const TransformedImageBounds &bounds);

/**
 * @brief Creates a shear matrix about the center of an image.
 *
 * The resulting transformation first translates the image center to the origin,
 * applies the shear transformation, and then translates the image back to its
 * original position.
 *
 * @param shearX Shear factor along the X-axis.
 * @param shearY Shear factor along the Y-axis.
 * @param bounds Bounding information of the current image.
 * @return A 3×3 homogeneous transformation matrix representing the shear
 *         about the image center.
 */
[[nodiscard]]
Matrix3x3 createShearCenterMatrix(double shearX, double shearY, const TransformedImageBounds &bounds);
