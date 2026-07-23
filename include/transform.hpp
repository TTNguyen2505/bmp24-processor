#pragma once

#include <tuple>
#include "bmp24.hpp"
#include "matrix.hpp"

/**
 * @brief Computes the dimensions of an image after applying a transformation matrix.
 * @param srcWidth Width of the source image.
 * @param srcHeight Height of the source image.
 * @param T 3×3 transformation matrix.
 * @return A pair containing the new image width and height.
 */
[[nodiscard]]
std::pair<int, int> calculateNewDimensions(int srcWidth, int srcHeight, const Matrix3x3 &T);

/**
 * @brief Computes a pixel value using bilinear interpolation.
 * @param srcImage Source image.
 * @param srcX Horizontal coordinate in the source image.
 * @param srcY Vertical coordinate in the source image.
 * @return The interpolated pixel.
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
 * @brief Translates an image.
 * @param img Reference to the image to process.
 * @param tx Translation along the x-axis.
 * @param ty Translation along the y-axis.
 * @return true if the transformation is applied successfully; false otherwise.
 */
bool applyTranslation(BMPImage &img, double tx, double ty);

/**
 * @brief Scales an image.
 * @param img Reference to the image to process.
 * @param sx Scale factor along the x-axis.
 * @param sy Scale factor along the y-axis.
 * @return true if the transformation is applied successfully; false otherwise.
 */
bool applyScale(BMPImage &img, double sx, double sy);

/**
 * @brief Rotates an image.
 * @param img Reference to the image to process.
 * @param theta Rotation angle in radians.
 * @return true if the transformation is applied successfully; false otherwise.
 */
bool applyRotation(BMPImage &img, double theta);

/**
 * @brief Shears an image.
 * @param img Reference to the image to process.
 * @param alpha Shear angle along the x-axis.
 * @param beta Shear angle along the y-axis.
 * @return true if the transformation is applied successfully; false otherwise.
 */
bool applyShear(BMPImage &img, double alpha, double beta);
