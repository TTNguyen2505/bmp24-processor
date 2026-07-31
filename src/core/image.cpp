#include "../../include/core/image.hpp"

#include <cmath>
#include <cstddef>

Pixel getPixelSafe(const BMPImage &img, std::int32_t x, std::int32_t y) {
    const std::int32_t width = getWidth(img);
    const std::int32_t height = std::abs(getHeight(img));

    if (x < 0 || y < 0 || x >= width || y >= height) {
        return Pixel{};
    }

    const std::size_t index =
            static_cast<std::size_t>(y) * static_cast<std::size_t>(width) + static_cast<std::size_t>(x);

    return img.data[index];
}
