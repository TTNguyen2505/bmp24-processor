#include "../include/util.hpp"

#include <chrono>
#include <filesystem>

bool loadBMP(const std::string &filename, BMPImage &img) {
    // TODO: Validate and load supported uncompressed 24-bit BMP files with correct padding.'
    return false;
}

bool saveBMP(const std::string &filename, const BMPImage &img) {
    // TODO: Write valid BMP headers, padded rows, pixel data, and report file errors.
    return false;
}

std::string generateOutputPath(const std::string &inputPath) {
    namespace fs = std::filesystem;

    const auto now = std::chrono::system_clock::now();
    const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();

    const fs::path path(inputPath);
    const fs::path parentDir = path.parent_path();
    const std::string stem = path.stem().string();
    const std::string extension = path.extension().string();

    const std::string newFilename = stem + "-" + std::to_string(ms) + extension;

    return parentDir.empty() ? newFilename : (parentDir / newFilename).string();
}

std::size_t calculatePadding(std::int32_t width) { return (4 - ((static_cast<std::size_t>(width) * 3) % 4)) % 4; }

std::uint8_t clampColor(double value) {
    if (value <= 0.0) {
        return 0u;
    }
    if (value >= 255.0) {
        return 255u;
    }
    return static_cast<std::uint8_t>(value + 0.5);
}

Pixel getPixelSafe(const BMPImage &img, std::int32_t x, std::int32_t y) {
    if (x < 0 || x >= getWidth(img) || y < 0 || y >= getHeight(img)) {
        return Pixel{0, 0, 0};
    }

    return img.data[y * getWidth(img) + x];
}
