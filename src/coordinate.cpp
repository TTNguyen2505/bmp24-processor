#include "../include/coordinate.hpp"

CoordinateVector3 pointToCoordinate3(double x, double y) { return {x, y, 1.0}; }

std::pair<double, double> coordinate3ToPoint(const CoordinateVector3 &point) {
    return {point.x / point.w, point.y / point.w};
}
