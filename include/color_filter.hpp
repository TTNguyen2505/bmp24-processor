#pragma once

#include "bmp24.hpp"
#include "matrix.hpp"

/**
 * @brief Applies a grayscale filter to the image.
 * @param img Reference to the BMP image to process.
 * @param amount Grayscale intensity factor a ∈ [0.0, 1.0].
 * @return `true` if the filter is applied successfully; `false` if amount is outside the valid range.
 */
bool applyGrayScale(BMPImage &img, double amount);

/**
 * @brief Applies a color inversion (negative) filter to the image.
 * @param img Reference to the BMP image to process.
 * @param amount Inversion intensity factor a ∈ [0.0, 1.0].
 * @return `true` if the filter is applied successfully; `false` if amount is outside the valid range.
 */
bool applyColorInversion(BMPImage &img, double amount);

/**
 * @brief Applies a sepia-tone filter to the image.
 * @param img Reference to the BMP image to process.
 * @param amount Sepia intensity factor a ∈ [0.0, 1.0].
 * @return `true` if the filter is applied successfully; `false` if amount is outside the valid range.
 */
bool applySepia(BMPImage &img, double amount);

/**
 * @brief Adjusts the image brightness.
 * @param img Reference to the BMP image to process.
 * @param amount Brightness adjustment factor.
 * @return `true` if the adjustment is applied successfully; `false` if amount is outside the valid range.
 */
bool applyBrightness(BMPImage &img, double amount);

/**
 * @brief Adjusts the image contrast.
 * @param img Reference to the BMP image to process.
 * @param amount Contrast adjustment factor.
 * @return `true` if the adjustment is applied successfully; `false` if amount is outside the valid range.
 */
bool applyContrast(BMPImage &img, double amount);

/**
 * @brief Adjusts the image color saturation.
 * @param img Reference to the BMP image to process.
 * @param amount Saturation adjustment factor.
 * @return `true` if the adjustment is applied successfully; `false` if amount is outside the valid range.
 */
bool applySaturate(BMPImage &img, double amount);