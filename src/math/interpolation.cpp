#include "math/interpolation.hpp"

#include <cmath>

#include "core/color.hpp"
#include "core/image.hpp"

Pixel bilinearInterpolate(const BMPImage &srcImage, double srcX, double srcY) {
    const std::int32_t x0 = static_cast<std::int32_t>(std::floor(srcX));
    const std::int32_t y0 = static_cast<std::int32_t>(std::floor(srcY));

    // Outside the source image
    if (x0 < 0 || x0 >= getWidth(srcImage) || y0 < 0 || y0 >= getHeight(srcImage)) {
        return Pixel{0, 0, 0};
    }

    const double dx = srcX - x0;
    const double dy = srcY - y0;

    // Bottom-right corner
    if (x0 == getWidth(srcImage) - 1 && y0 == getHeight(srcImage) - 1) {
        return getPixelSafe(srcImage, x0, y0);
    }

    // Right border
    if (x0 == getWidth(srcImage) - 1) {
        const Pixel p0 = getPixelSafe(srcImage, x0, y0);
        const Pixel p1 = getPixelSafe(srcImage, x0, y0 + 1);

        return Pixel{clampColor((1.0 - dy) * p0.red + dy * p1.red), clampColor((1.0 - dy) * p0.green + dy * p1.green),
                     clampColor((1.0 - dy) * p0.blue + dy * p1.blue)};
    }

    // Bottom border
    if (y0 == getHeight(srcImage) - 1) {
        const Pixel p0 = getPixelSafe(srcImage, x0, y0);
        const Pixel p1 = getPixelSafe(srcImage, x0 + 1, y0);

        return Pixel{clampColor((1.0 - dx) * p0.red + dx * p1.red), clampColor((1.0 - dx) * p0.green + dx * p1.green),
                     clampColor((1.0 - dx) * p0.blue + dx * p1.blue)};
    }

    // Bilinear interpolation
    const Pixel p00 = getPixelSafe(srcImage, x0, y0);
    const Pixel p10 = getPixelSafe(srcImage, x0 + 1, y0);
    const Pixel p01 = getPixelSafe(srcImage, x0, y0 + 1);
    const Pixel p11 = getPixelSafe(srcImage, x0 + 1, y0 + 1);

    const double w00 = (1.0 - dx) * (1.0 - dy);
    const double w10 = dx * (1.0 - dy);
    const double w01 = (1.0 - dx) * dy;
    const double w11 = dx * dy;

    return Pixel{clampColor(w00 * p00.blue + w10 * p10.blue + w01 * p01.blue + w11 * p11.blue),
                 clampColor(w00 * p00.green + w10 * p10.green + w01 * p01.green + w11 * p11.green),
                 clampColor(w00 * p00.red + w10 * p10.red + w01 * p01.red + w11 * p11.red)};
}
