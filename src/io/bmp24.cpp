#include "../../include/io/bmp24.hpp"

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <type_traits>

#include "../../include/math/geometry.hpp"

std::int32_t getWidth(const BMPImage &image) {
    return std::visit([](auto &&header) { return header.width; }, image.infoHeader);
}

std::int32_t getHeight(const BMPImage &image) {
    return std::visit([](auto &&header) { return header.height; }, image.infoHeader);
}

std::uint16_t getBitCount(const BMPImage &image) {
    return std::visit([](auto &&header) { return header.bitCount; }, image.infoHeader);
}

void setWidth(BMPImage &image, std::int32_t width) {
    std::visit([width](auto &header) { header.width = width; }, image.infoHeader);
}

void setHeight(BMPImage &image, std::int32_t height) {
    std::visit([height](auto &header) { header.height = height; }, image.infoHeader);
}

void setImageSize(BMPImage &image, std::uint32_t size) {
    std::visit([size](auto &header) { header.sizeImage = size; }, image.infoHeader);
}

TransformedImageBounds getImageBounds(const BMPImage &image) { return {getWidth(image), getHeight(image), 0, 0}; }

const BMPInfoHeader &getInfoHeader(const BMPImage &image) {
    return std::visit([](const auto &h) -> const BMPInfoHeader & { return h; }, image.infoHeader);
}

BMPInfoHeader &getInfoHeader(BMPImage &image) {
    return std::visit([](auto &h) -> BMPInfoHeader & { return h; }, image.infoHeader);
}
