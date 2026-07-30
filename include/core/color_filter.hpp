#pragma once

#include "io/bmp24.hpp"
#include "math/matrix.hpp"

/**
 * @brief Applies a 4x4 color transformation matrix to a pixel.
 * @param matrix Color filter matrix.
 * @param pixel Input pixel.
 * @return Transformed pixel with clamped RGB channels.
 */
[[nodiscard]]
Pixel applyColorMatrix(const Matrix4x4 &matrix, const Pixel &pixel);

/**
 * @brief Creates a grayscale filter matrix.
 * @param amount Grayscale intensity factor in the range [0.0, 1.0].
 * @return A grayscale filter matrix.
 */
[[nodiscard]]
Matrix4x4 createGrayscaleMatrix(double amount);

/**
 * @brief Creates a sepia filter matrix.
 * @param amount Sepia intensity factor in the range [0.0, 1.0].
 * @return A sepia filter matrix.
 */
[[nodiscard]]
Matrix4x4 createSepiaMatrix(double amount);

/**
 * @brief Creates a color inversion filter matrix.
 * @param amount Inversion intensity factor in the range [0.0, 1.0].
 * @return An inversion filter matrix.
 */
[[nodiscard]]
Matrix4x4 createInvertMatrix(double amount);

/**
 * @brief Creates a brightness adjustment matrix.
 * @param amount Brightness adjustment factor in the range [0.0, +∞).
 * @return A brightness adjustment matrix.
 */
[[nodiscard]]
Matrix4x4 createBrightnessMatrix(double amount);

/**
 * @brief Creates a contrast adjustment matrix.
 * @param amount Contrast adjustment factor in the range [0.0, +∞).
 * @return A contrast adjustment matrix.
 */
[[nodiscard]]
Matrix4x4 createContrastMatrix(double amount);

/**
 * @brief Creates a saturation adjustment matrix.
 * @param amount Saturation adjustment factor in the range [0.0, +∞).
 * @return A saturation adjustment matrix.
 */
[[nodiscard]]
Matrix4x4 createSaturateMatrix(double amount);
