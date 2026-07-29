#pragma once

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <variant>
#include <vector>

#pragma pack(push, 1)

/**
 * @brief BMP File Header structure (14 bytes)
 */
struct BMPFileHeader {
    std::uint16_t type{0x4D42}; /**< Magic number ('BM' or 0x4D42) */
    std::uint32_t size{0}; /**< The size of the file in bytes */
    std::uint16_t reserved1{0}; /**< Reserved, must be 0 */
    std::uint16_t reserved2{0}; /**< Reserved, must be 0 */
    std::uint32_t offset{0}; /**< The offset of the pixel data in the file */
};

/**
 * @brief Standard BITMAPINFOHEADER structure (40 bytes)
 */
struct BMPInfoHeader {
    std::uint32_t size{40}; /**< Size of this header (40 bytes) */
    std::int32_t width{0}; /**< Width of the image in pixels */
    std::int32_t height{0}; /**< Height of the image in pixels */
    std::uint16_t planes{1}; /**< Number of color planes (must be 1) */
    std::uint16_t bitCount{24}; /**< Bits per pixel (e.g., 24 for 24-bit BMP) */
    std::uint32_t compression{0}; /**< Compression type (0 = BI_RGB) */
    std::uint32_t sizeImage{0}; /**< Size of raw pixel data */
    std::int32_t xPixelsPerMeter{0}; /**< Horizontal resolution (pixels/meter) */
    std::int32_t yPixelsPerMeter{0}; /**< Vertical resolution (pixels/meter) */
    std::uint32_t colorsUsed{0}; /**< Number of colors in color table */
    std::uint32_t colorsImportant{0}; /**< Number of important colors */
};

/**
 * @brief BITMAPV4HEADER structure (108 bytes) - Supporting Color Masks & Space
 */
struct BMPV4Header : public BMPInfoHeader {
    std::uint32_t redMask{0};
    std::uint32_t greenMask{0};
    std::uint32_t blueMask{0};
    std::uint32_t alphaMask{0};
    std::uint32_t csType{0};
    std::uint8_t endpoints[36]{0};
    std::uint32_t gammaRed{0};
    std::uint32_t gammaGreen{0};
    std::uint32_t gammaBlue{0};
};

/**
 * @brief BITMAPV5HEADER structure (124 bytes) - Support ICC Profile & Rendering Intent
 */
struct BMPV5Header : public BMPV4Header {
    std::uint32_t intent{0};
    std::uint32_t profile_data{0};
    std::uint32_t profile_size{0};
    std::uint32_t reserved{0};
};

/**
 * @brief Pixel structure for 24-bit BGR image
 */
struct Pixel {
    std::uint8_t blue{0}; /**< Blue component */
    std::uint8_t green{0}; /**< Green component */
    std::uint8_t red{0}; /**< Red component */
};

/**
 * @brief Represents a 4D color vector using double-precision floating-point values
 *        for intermediate calculation in BMP image color filtering.
 *
 * @details This structure holds RGB color components in the range [0.0, 255.0]
 *          along with a homogeneous coordinate 'w' set to 1.0. The 4D vector representation
 *          enables affine color transformation via 4x4 matrix multiplication.
 */

/**
 * @brief Variant which defines DIB Header (support InfoHeader, V4, V5)
 */
using DIBHeader = std::variant<BMPInfoHeader, BMPV4Header, BMPV5Header>;

/**
 * @brief BMP Image class/structure
 */
struct BMPImage {
    BMPFileHeader fileHeader; /**< The file header */
    DIBHeader infoHeader{BMPInfoHeader{}}; /**< The info header */
    std::vector<Pixel> data; /**< The pixel data */
};

/**
 * @brief Gets the width of a BMP image.
 *
 * @param image The BMP image.
 * @return The image width in pixels.
 */
[[nodiscard]]
std::int32_t getWidth(const BMPImage &image);

/**
 * @brief Gets the height of a BMP image.
 *
 * @param image The BMP image.
 * @return The image height in pixels.
 */
[[nodiscard]]
std::int32_t getHeight(const BMPImage &image);

/**
 * @brief Gets the color depth of a BMP image.
 *
 * Returns the number of bits used to represent a single pixel.
 *
 * @param image The BMP image.
 * @return The number of bits per pixel.
 */
[[nodiscard]]
std::uint16_t getBitCount(const BMPImage &image);

#pragma pack(pop)
