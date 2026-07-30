#pragma once

#include <cstdint>
#include <string>

#include "bmp24.hpp"

/**
 * @brief Loads a 24-bit BMP image from a file.
 *
 * @param filename Input BMP file path.
 * @param img Destination image object.
 * @return true if the image is loaded successfully; otherwise false.
 */
bool loadBMP(const std::string &filename, BMPImage &img);

/**
 * @brief Saves a BMP image to a file.
 *
 * @param filename Output BMP file path.
 * @param img Image to save.
 * @return true if the image is saved successfully; otherwise false.
 */
bool saveBMP(const std::string &filename, const BMPImage &img);

/**
 * @brief Generates an output file path based on the input file name and current timestamp.
 *
 * Example: "input.bmp" -> "input-1718293849123.bmp"
 *          "dir/image.jpg" -> "dir/image-1718293849123.jpg"
 *
 * @param inputPath Input file path.
 * @return Generated output file path.
 */
[[nodiscard]]
std::string generateOutputPath(const std::string &inputPath);

/**
 * @brief Calculates the padding bytes required for each BMP row.
 *
 * @param width Image width in pixels.
 * @return Number of padding bytes (0-3).
 */
[[nodiscard]]
std::size_t calculatePadding(std::int32_t width);

/**
 * @brief Clamps a color value to the valid 8-bit range [0, 255].
 *
 * @param value Input color value.
 * @return Clamped color value.
 */
[[nodiscard]]
std::uint8_t clampColor(double value);

/**
 * @brief Returns the pixel at the specified coordinates.
 *
 * If the coordinates are outside the image boundaries, a black pixel is returned.
 *
 * @param img Source image.
 * @param x X-coordinate.
 * @param y Y-coordinate.
 * @return Pixel at the specified position, or a black pixel if out of bounds.
 */
[[nodiscard]]
Pixel getPixelSafe(const BMPImage &img, std::int32_t x, std::int32_t y);
