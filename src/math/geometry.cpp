#include "math/geometry.hpp"

#include <algorithm>
#include <cmath>
#include <cstddef>
constexpr double PI = 3.14159265358979323846;

double degToRad(double degree) { return degree * PI / 180.0; }

TransformedImageBounds calculateNewDimensions(const TransformedImageBounds &bounds, const Matrix3x3 &T) {

    const double left = static_cast<double>(bounds.minX);
    const double top = static_cast<double>(bounds.minY);

    const double right = left + bounds.width - 1.0;
    const double bottom = top + bounds.height - 1.0;

    const CoordinateVector3 corners[4] = {T * CoordinateVector3{left, top, 1.0}, T * CoordinateVector3{right, top, 1.0},
                                          T * CoordinateVector3{left, bottom, 1.0},
                                          T * CoordinateVector3{right, bottom, 1.0}};

    double minX = corners[0].x;
    double maxX = corners[0].x;
    double minY = corners[0].y;
    double maxY = corners[0].y;

    for (std::size_t i = 1; i < 4; ++i) {
        minX = std::min(minX, corners[i].x);
        maxX = std::max(maxX, corners[i].x);

        minY = std::min(minY, corners[i].y);
        maxY = std::max(maxY, corners[i].y);
    }

    const std::int32_t newMinX = static_cast<std::int32_t>(std::floor(minX));

    const std::int32_t newMinY = static_cast<std::int32_t>(std::floor(minY));

    const std::int32_t newWidth = static_cast<std::int32_t>(std::ceil(maxX)) - newMinX + 1;

    const std::int32_t newHeight = static_cast<std::int32_t>(std::ceil(maxY)) - newMinY + 1;

    return {newWidth, newHeight, newMinX, newMinY};
}
