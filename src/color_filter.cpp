#include "../include/color_filter.hpp"
#include "../include/matrix.hpp"
#include "../include/util.hpp"

bool applyGrayScale(BMPImage &img, double amount) {
    // TODO: Validate amount, apply grayscale transformation to pixels, clamp channels, and report success.
    return false;
}

bool applyColorInversion(BMPImage &img, double amount) {
    // TODO: Validate amount, apply inversion transformation to pixels, clamp channels, and report success.
    return false;
}

bool applySepia(BMPImage &img, double amount) {
    // TODO: Validate amount, apply sepia transformation to pixels, clamp channels, and report success.
    return false;
}

bool applyBrightness(BMPImage &img, double amount) {
    // TODO: Validate amount, apply brightness transformation to pixels, clamp channels, and report success.
    return false;
}

bool applyContrast(BMPImage &img, double amount) {
    // TODO: Validate amount, apply contrast transformation to pixels, clamp channels, and report success.
    return false;
}

bool applyFilterMatrix(BMPImage &img, const Matrix4x4 &matrix) {
    for (auto &pixel : img.data) {
        Vector4 color{static_cast<double>(pixel.red), static_cast<double>(pixel.green), static_cast<double>(pixel.blue), 1.0};
        Vector4 transformed = matrix * color;
        pixel.red = clampColor(transformed.x);
        pixel.green = clampColor(transformed.y);
        pixel.blue = clampColor(transformed.z);
    }
    return true;
}

bool applySaturate(BMPImage &img, double amount) {
    // TODO: Validate amount, apply saturation transformation to pixels, clamp channels, and report success.
    return false;
}
