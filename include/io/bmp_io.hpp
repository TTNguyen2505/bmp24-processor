#pragma once

#include <cstddef>
#include <cstdint>
#include <string>

#include "io/bmp24.hpp"

/**
 * @brief Calculates the row padding size in bytes for a BMP image line.
 *
 * In the BMP file format, each scanline must be padded to a multiple of 4 bytes.
 * This function computes the number of padding bytes required at the end of
 * each row based on the image width (assuming 24-bit RGB / 3 bytes per pixel).
 *
 * @param width The width of the image in pixels.
 * @return std::size_t The number of padding bytes per row (in the range [0, 3]).
 *
 * @note Formula used: (4 - ((width * 3) % 4)) % 4
 */
[[nodiscard]]
std::size_t calculatePadding(std::int32_t width);

/**
 * @brief Loads a BMP image from a specified file.
 *
 * @param[in] filename Path to the input BMP file.
 * @param[out] image Destination object to store the loaded BMP image data.
 * @return `true` if the image was successfully loaded, `false` otherwise.
 */
[[nodiscard]]
bool loadBMP(const std::string &filename, BMPImage &image);

/**
 * @brief Saves a BMP image to a specified file.
 *
 * @param[in] filename Path to the output destination file.
 * @param[in] image BMPImage object containing the data to write.
 * @return `true` if the image was successfully saved, `false` otherwise.
 */
[[nodiscard]]
bool saveBMP(const std::string &filename, const BMPImage &image);
