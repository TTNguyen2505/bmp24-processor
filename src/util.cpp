#include "../include/util.hpp"

BMPImage createImage(std::int32_t width, std::int32_t height) {
    // TODO: Create initialized 24-bit BMP headers, pixel storage, and black image pixels.
}

bool loadBMP(const std::string &filename, BMPImage &img) {
    // TODO: Validate and load supported uncompressed 24-bit BMP files with correct padding.
}

bool saveBMP(const std::string &filename, const BMPImage &img) {
    // TODO: Write valid BMP headers, padded rows, pixel data, and report file errors.
}

std::string generateOutputPath(const std::string &inputPath) {
    // TODO: Generate a processed filename beside the input while preserving its extension.
}

inline std::size_t calculatePadding(std::int32_t width) {
    return (4 - ((static_cast<std::size_t>(width) * 3) % 4)) % 4;
}

std::uint8_t clampColor(double value) {
    // TODO: Restrict a floating-point channel value to the valid 8-bit range.
}

Pixel getPixelSafe(const BMPImage &img, std::int32_t x, std::int32_t y) {
    // TODO:  Return the requested pixel or black when coordinates exceed image boundaries.
}
