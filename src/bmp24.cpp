#include "../include/bmp24.hpp"

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
