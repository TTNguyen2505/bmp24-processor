#include "../../include/io/bmp_io.hpp"

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <type_traits>

std::size_t calculatePadding(std::int32_t width) { return (4 - ((static_cast<std::size_t>(width) * 3) % 4)) % 4; }

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

template<typename T>
bool writeStruct(std::ostream &os, const T &value) {
    static_assert(std::is_trivially_copyable_v<T>);
    return static_cast<bool>(os.write(reinterpret_cast<const char *>(&value), sizeof(T)));
}

bool writeFileHeader(std::ostream &os, BMPFileHeader header) {
    header.type = 0x4D42;
    header.reserved1 = 0;
    header.reserved2 = 0;
    return writeStruct(os, header);
}

bool writeDIBHeader(std::ostream &os, DIBHeader header) {
    return std::visit(
            [&os](auto &dibHeader) {
                using HeaderT = std::decay_t<decltype(dibHeader)>;
                dibHeader.size = static_cast<std::uint32_t>(sizeof(HeaderT));
                return writeStruct(os, dibHeader);
            },
            header);
}

bool writePixelData(std::ostream &os, const BMPImage &image) {
    const auto width = getWidth(image);
    const auto height = getHeight(image);
    const auto absHeight = static_cast<std::size_t>(std::abs(height));

    if (width <= 0 || height == 0)
        return false;

    const auto expectedPixels = static_cast<std::size_t>(width) * absHeight;
    if (image.data.size() != expectedPixels)
        return false;

    const std::size_t rowBytes = static_cast<std::size_t>(width) * sizeof(Pixel);
    const std::size_t rowSize = rowBytes + calculatePadding(width);
    const bool bottomUp = height > 0;

    std::vector<std::uint8_t> row(rowSize, 0u);

    for (std::size_t y = 0; y < absHeight; ++y) {
        const std::size_t srcRow = bottomUp ? (absHeight - 1 - y) : y;
        const Pixel *srcPixels = image.data.data() + srcRow * static_cast<std::size_t>(width);

        std::memcpy(row.data(), srcPixels, rowBytes);

        if (!os.write(reinterpret_cast<const char *>(row.data()), static_cast<std::streamsize>(rowSize)))
            return false;
    }

    return true;
}

void updateHeaders(BMPImage &image) {
    auto &file = image.fileHeader;
    auto &info = getInfoHeader(image);

    const auto width = getWidth(image);
    const auto height = std::abs(getHeight(image));
    const auto padding = calculatePadding(width);

    info.size =
            static_cast<std::uint32_t>(std::visit([](const auto &header) { return sizeof(header); }, image.infoHeader));
    info.planes = 1;
    info.bitCount = 24;
    info.compression = 0;
    info.colorsUsed = 0;
    info.colorsImportant = 0;
    info.sizeImage = static_cast<std::uint32_t>((static_cast<std::size_t>(width) * sizeof(Pixel) + padding) *
                                                static_cast<std::size_t>(height));

    file.type = 0x4D42;
    file.reserved1 = 0;
    file.reserved2 = 0;
    file.offset = sizeof(BMPFileHeader) + info.size;
    file.size = file.offset + info.sizeImage;
}

bool saveBMP(const std::string &filename, const BMPImage &image) {
    std::ofstream file(filename, std::ios::binary);

    if (!file)
        return false;

    BMPImage output = image;

    if (!validateBMPHeader(getInfoHeader(output)))
        return false;

    updateHeaders(output);

    if (!writeFileHeader(file, output.fileHeader))
        return false;

    if (!writeDIBHeader(file, output.infoHeader))
        return false;

    return writePixelData(file, output);
}
