#pragma once

#include <string>

#include "bmp24.hpp"

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