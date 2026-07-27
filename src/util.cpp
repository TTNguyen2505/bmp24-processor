#include "../include/util.hpp"

#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include <utility>
#include <vector>

BMPImage createImage(std::int32_t width, std::int32_t height) {
    if (width <= 0 || height <= 0) {
        return BMPImage{};
    }

    BMPImage image{};
    image.fileHeader.type = 0x4D42;
    image.fileHeader.size = 0;
    image.fileHeader.reserved1 = 0;
    image.fileHeader.reserved2 = 0;
    image.fileHeader.offset = 14 + 40;

    BMPInfoHeader header{};
    header.size = 40;
    header.width = width;
    header.height = height;
    header.planes = 1;
    header.bitCount = 24;
    header.compression = 0;
    header.sizeImage = 0;
    header.xPixelsPerMeter = 0;
    header.yPixelsPerMeter = 0;
    header.colorsUsed = 0;
    header.colorsImportant = 0;
    image.infoHeader = header;
    const std::size_t pixelCount = static_cast<std::size_t>(width) * static_cast<std::size_t>(height);
    image.data.assign(pixelCount, Pixel{});
    return image;
}

bool loadBMP(const std::string &filename, BMPImage &img) {
    std::ifstream input(filename, std::ios::binary | std::ios::ate);
    if (!input) {
        return false;
    }

    const std::streamoff fileSize = input.tellg();
    input.seekg(0, std::ios::beg);
    if (fileSize < 0) {
        return false;
    }

    BMPFileHeader fileHeader{};
    input.read(reinterpret_cast<char *>(&fileHeader), sizeof(fileHeader));
    if (!input || fileHeader.type != 0x4D42 || fileHeader.reserved1 != 0 || fileHeader.reserved2 != 0) {
        return false;
    }

    std::uint32_t dibSize = 0;
    input.read(reinterpret_cast<char *>(&dibSize), sizeof(dibSize));
    if (!input || (dibSize != 40 && dibSize != 108 && dibSize != 124)) {
        return false;
    }

    std::vector<std::uint8_t> dibBuffer(dibSize);
    if (dibSize > 0) {
        input.read(reinterpret_cast<char *>(dibBuffer.data()), dibSize);
        if (!input) {
            return false;
        }
    }

    BMPImage loaded{};
    loaded.fileHeader = fileHeader;

    if (dibSize == 40) {
        BMPInfoHeader header{};
        std::memcpy(&header, dibBuffer.data(), sizeof(header));
        loaded.infoHeader = header;
    } 
    else if (dibSize == 108) {
        BMPV4Header header{};
        std::memcpy(&header, dibBuffer.data(), sizeof(header));
        loaded.infoHeader = header;
    }
     else {
        BMPV5Header header{};
        std::memcpy(&header, dibBuffer.data(), sizeof(header));
        loaded.infoHeader = header;
    }

    const auto width = getWidth(loaded);
    const auto height = getHeight(loaded);
    const auto bitCount = getBitCount(loaded);
    const auto compression = std::visit([](auto &&header) { return header.compression; }, loaded.infoHeader);
    const auto planes = std::visit([](auto &&header) { return header.planes; }, loaded.infoHeader);

    if (width <= 0 || height == 0 || bitCount != 24 || compression != 0 || planes != 1) {
        return false;
    }

    const std::int32_t absHeight = std::abs(height);
    const std::size_t rowStride = static_cast<std::size_t>(width) * 3 + calculatePadding(width);
    const std::size_t pixelCount = static_cast<std::size_t>(width) * static_cast<std::size_t>(absHeight);

    if (fileHeader.offset < static_cast<std::uint32_t>(14 + dibSize)) {
        return false;
    }

    const std::uint64_t expectedBytes = static_cast<std::uint64_t>(fileHeader.offset) +
        static_cast<std::uint64_t>(rowStride) * static_cast<std::uint64_t>(absHeight);
    if (static_cast<std::uint64_t>(fileSize) < expectedBytes) {
        return false;
    }

    loaded.data.assign(pixelCount, Pixel{});

    input.seekg(fileHeader.offset, std::ios::beg);
    std::vector<std::uint8_t> rowBuffer(rowStride);
    for (std::int32_t y = 0; y < absHeight; ++y) {
        input.read(reinterpret_cast<char *>(rowBuffer.data()), rowStride);
        if (!input) {
            return false;
        }

        const std::int32_t logicalRow = (height > 0) ? (absHeight - 1 - y) : y;
        for (std::int32_t x = 0; x < width; ++x) {
            const std::size_t offset = static_cast<std::size_t>(x) * 3;
            const std::size_t index = static_cast<std::size_t>(logicalRow) * static_cast<std::size_t>(width) + static_cast<std::size_t>(x);
            loaded.data[index].blue = rowBuffer[offset];
            loaded.data[index].green = rowBuffer[offset + 1];
            loaded.data[index].red = rowBuffer[offset + 2];
        }
    }

    img = std::move(loaded);
    return true;
}

bool saveBMP(const std::string &filename, const BMPImage &img) {
    std::ofstream output(filename, std::ios::binary);
    if (!output) {
        return false;
    }

    const auto width = getWidth(img);
    const auto height = getHeight(img);
    if (width <= 0 || height == 0) {
        return false;
    }

    const std::int32_t absHeight = std::abs(height);
    const std::size_t rowStride = static_cast<std::size_t>(width) * 3 + calculatePadding(width);
    const std::size_t pixelDataSize = rowStride * static_cast<std::size_t>(absHeight);

    std::size_t dibSize = std::visit([](const auto &header) { return static_cast<std::size_t>(header.size); }, img.infoHeader);
    BMPFileHeader fileHeader{};
    fileHeader.type = 0x4D42;
    fileHeader.size = static_cast<std::uint32_t>(14 + dibSize + pixelDataSize);
    fileHeader.offset = static_cast<std::uint32_t>(14 + dibSize);

    output.write(reinterpret_cast<const char *>(&fileHeader), sizeof(fileHeader));
    if (!output) {
        return false;
    }

    std::visit([&output](const auto &header) {
        output.write(reinterpret_cast<const char *>(&header), sizeof(header));
    }, img.infoHeader);
    if (!output) {
        return false;
    }

    if (img.data.size() < static_cast<std::size_t>(width) * static_cast<std::size_t>(absHeight)) {
        return false;
    }

    std::vector<std::uint8_t> rowBuffer(rowStride, 0);
    for (std::int32_t y = 0; y < absHeight; ++y) {
        const std::int32_t sourceRow = (height > 0) ? (absHeight - 1 - y) : y;
        for (std::int32_t x = 0; x < width; ++x) {
            const std::size_t index = static_cast<std::size_t>(sourceRow) * static_cast<std::size_t>(width) + static_cast<std::size_t>(x);
            const Pixel &pixel = img.data[index];
            const std::size_t offset = static_cast<std::size_t>(x) * 3;
            rowBuffer[offset] = pixel.blue;
            rowBuffer[offset + 1] = pixel.green;
            rowBuffer[offset + 2] = pixel.red;
        }

        output.write(reinterpret_cast<const char *>(rowBuffer.data()), rowStride);
        if (!output) {
            return false;
        }
    }

    return true;
}

std::string generateOutputPath(const std::string &inputPath) {
    const std::size_t dotPosition = inputPath.find_last_of('.');
    if (dotPosition == std::string::npos) {
        return inputPath + "_processed";
    }

    return inputPath.substr(0, dotPosition) + "_processed" + inputPath.substr(dotPosition);
}

inline std::size_t calculatePadding(std::int32_t width) {
    return (4 - ((static_cast<std::size_t>(width) * 3) % 4)) % 4;
}

std::uint8_t clampColor(double value) {
    if (value < 0.0) {
        return 0;
    }
    if (value > 255.0) {
        return 255;
    }
    return static_cast<std::uint8_t>(std::lround(value));
}

Pixel getPixelSafe(const BMPImage &img, std::int32_t x, std::int32_t y) {
    const std::int32_t width = getWidth(img);
    const std::int32_t height = std::abs(getHeight(img));
    if (x < 0 || y < 0 || x >= width || y >= height) {
        return Pixel{};
    }

    const std::size_t index = static_cast<std::size_t>(y) * static_cast<std::size_t>(width) + static_cast<std::size_t>(x);
    return img.data[index];
}
