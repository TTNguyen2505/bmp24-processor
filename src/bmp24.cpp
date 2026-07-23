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
