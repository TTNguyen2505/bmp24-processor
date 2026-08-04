#include "../../include/core/color_filter.hpp"

#include "../../include/core/color.hpp"
#include "../../include/math/matrix.hpp"

#include <algorithm>

Matrix4x4 createGrayscaleMatrix(double amount) {
    const double r = 0.299 * amount;
    const double g = 0.587 * amount;
    const double b = 0.114 * amount;
    const double inv = 1.0 - amount;

    return Matrix4x4{{{inv + r, g, b, 0.0}, {r, inv + g, b, 0.0}, {r, g, inv + b, 0.0}, {0.0, 0.0, 0.0, 1.0}}};
}

Matrix4x4 createSepiaMatrix(double amount) {
    const double inv = 1.0 - amount;

    return Matrix4x4{{{inv + 0.393 * amount, 0.769 * amount, 0.189 * amount, 0.0},
                      {0.349 * amount, inv + 0.686 * amount, 0.168 * amount, 0.0},
                      {0.272 * amount, 0.534 * amount, inv + 0.131 * amount, 0.0},
                      {0.0, 0.0, 0.0, 1.0}}};
}

Matrix4x4 createInvertMatrix(double amount) {
    const double diag = 1.0 - 2.0 * amount;
    const double trans = 255.0 * amount;

    return Matrix4x4{{{diag, 0.0, 0.0, trans}, {0.0, diag, 0.0, trans}, {0.0, 0.0, diag, trans}, {0.0, 0.0, 0.0, 1.0}}};
}

Matrix4x4 createBrightnessMatrix(double amount) {
    return Matrix4x4{{{amount, 0.0, 0.0, 0.0}, {0.0, amount, 0.0, 0.0}, {0.0, 0.0, amount, 0.0}, {0.0, 0.0, 0.0, 1.0}}};
}

Matrix4x4 createContrastMatrix(double amount) {
    const double offset = (1.0 - amount) * 127.5;

    return Matrix4x4{
            {{amount, 0.0, 0.0, offset}, {0.0, amount, 0.0, offset}, {0.0, 0.0, amount, offset}, {0.0, 0.0, 0.0, 1.0}}};
}

Matrix4x4 createSaturateMatrix(double amount) {
    const double inv = 1.0 - amount;
    const double lr = 0.299 * inv;
    const double lg = 0.587 * inv;
    const double lb = 0.114 * inv;

    return Matrix4x4{
            {{lr + amount, lg, lb, 0.0}, {lr, lg + amount, lb, 0.0}, {lr, lg, lb + amount, 0.0}, {0.0, 0.0, 0.0, 1.0}}};
}

Pixel applyColorMatrix(const Matrix4x4 &matrix, const Pixel &pixel) {
    ColorVector4 vector = pixelToColor4(pixel);
    vector = matrix * vector;
    return color4ToPixel(vector);
}
