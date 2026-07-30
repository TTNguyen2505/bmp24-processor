#include "../include/bmp24.hpp"

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <type_traits>

#include "../include/transform.hpp"
#include "../include/util.hpp"

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

template<typename T>
bool readStruct(std::istream &is, T &value) {
    static_assert(std::is_trivially_copyable_v<T>);
    return static_cast<bool>(is.read(reinterpret_cast<char *>(&value), sizeof(T)));
}

bool readFileHeader(std::istream &is, BMPFileHeader &header) {
    if (!readStruct(is, header))
        return false;

    return header.type == 0x4D42;
}

bool readDIBHeader(std::istream &is, DIBHeader &dibHeader) {
    std::uint32_t headerSize{};

    if (!readStruct(is, headerSize))
        return false;

    is.seekg(-static_cast<std::streamoff>(sizeof(headerSize)), std::ios::cur);

    switch (headerSize) {
        case sizeof(BMPInfoHeader): {
            BMPInfoHeader h;
            if (!readStruct(is, h))
                return false;

            dibHeader = h;
            break;
        }

        case sizeof(BMPV4Header): {
            BMPV4Header h;
            if (!readStruct(is, h))
                return false;

            dibHeader = h;
            break;
        }

        case sizeof(BMPV5Header): {
            BMPV5Header h;
            if (!readStruct(is, h))
                return false;

            dibHeader = h;
            break;
        }

        default:
            return false;
    }

    return true;
}

bool validateBMPHeader(const BMPInfoHeader &header) {
    return header.width > 0 && header.height != 0 && header.bitCount == 24 && header.compression == 0;
}

bool readPixelData(std::istream &is, const BMPFileHeader &fileHeader, const BMPInfoHeader &infoHeader,
                   std::vector<Pixel> &pixels) {
    const int width = infoHeader.width;
    const int height = std::abs(infoHeader.height);

    const bool bottomUp = infoHeader.height > 0;

    const std::size_t rowSize = ((width * sizeof(Pixel) + 3) / 4) * 4;

    pixels.resize(static_cast<std::size_t>(width) * height);

    std::vector<std::uint8_t> row(rowSize);

    is.seekg(fileHeader.offset, std::ios::beg);

    for (int y = 0; y < height; ++y) {
        if (!is.read(reinterpret_cast<char *>(row.data()), rowSize))
            return false;

        const int dstRow = bottomUp ? height - 1 - y : y;

        std::memcpy(pixels.data() + dstRow * width, row.data(), static_cast<std::size_t>(width) * sizeof(Pixel));
    }

    std::cout << "R: " << (int) pixels[0].red << " G: " << (int) pixels[0].green << " B: " << (int) pixels[0].blue
              << std::endl;
    return true;
}

bool loadBMP(const std::string &filename, BMPImage &image) {
    std::ifstream file(filename, std::ios::binary);

    if (!file)
        return false;

    if (!readFileHeader(file, image.fileHeader))
        return false;

    if (!readDIBHeader(file, image.infoHeader))
        return false;

    const auto &info = getInfoHeader(image);

    if (!validateBMPHeader(info))
        return false;

    return readPixelData(file, image.fileHeader, info, image.data);
}
