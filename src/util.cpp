#include "../include/util.hpp"

#include <chrono>
#include <filesystem>

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
    // TODO: Restrict a floating-point channel value to the valid 8-bit range.
}

// Lấy pixel tại tọa độ (x, y) một cách an toàn.
// Nếu tọa độ ngoài phạm vi thì trả về pixel đen thay vì gây lỗi.
Pixel getPixelSafe(const BMPImage &img,
                   std::int32_t x,
                   std::int32_t y) {
    const std::int32_t width = getWidth(img);
    const std::int32_t height = std::abs(getHeight(img));

    if (x < 0 || y < 0 || x >= width || y >= height) {
        return Pixel{};
    }

    const std::size_t index =
        static_cast<std::size_t>(y) *
            static_cast<std::size_t>(width) +
        static_cast<std::size_t>(x);

    return img.data[index];
}