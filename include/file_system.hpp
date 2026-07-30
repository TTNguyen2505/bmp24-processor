#pragma once

#include <string>

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