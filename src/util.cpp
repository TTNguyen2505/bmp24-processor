#include "../include/util.hpp"

#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include <utility>
#include <vector>

// Tạo một ảnh BMP mới với kích thước width x height.
// Nếu chiều cao là số âm thì vẫn được chấp nhận, vì BMP dùng dấu âm để biểu thị ảnh được lưu theo hướng từ trên xuống.
BMPImage createImage(std::int32_t width, std::int32_t height) {
    if (width <= 0 || height == 0) {
        return BMPImage{};
    }

    BMPImage image{};

    // Thiết lập header của file BMP.
    image.fileHeader.type = 0x4D42; // Dấu hiệu nhận diện file BMP ("BM")
    image.fileHeader.reserved1 = 0; // Reserved field, bắt buộc là 0
    image.fileHeader.reserved2 = 0; // Reserved field, bắt buộc là 0
    image.fileHeader.offset = 14 + 40; // Vị trí bắt đầu dữ liệu pixel: 14-byte file header + 40-byte DIB header

    // Thiết lập DIB header chuẩn cho BMP 24-bit, không nén.
    BMPInfoHeader header{};
    header.size = 40;             // Kích thước của BITMAPINFOHEADER chuẩn (40 byte)
    header.width = width;         // Chiều rộng ảnh
    header.height = height;       // Chiều cao ảnh (âm là top-down, dương là bottom-up)
    header.planes = 1;            // Số mặt phẳng màu, bắt buộc là 1
    header.bitCount = 24;         // 24 bit/pixel, 8 bit cho mỗi kênh R/G/B
    header.compression = 0;       // 0 = BI_RGB, không nén

    // Tính số byte mỗi dòng (bao gồm padding) và kích thước dữ liệu pixel.
    const std::int32_t absHeight = std::abs(height);
    const std::size_t rowStride = static_cast<std::size_t>(width) * 3 + calculatePadding(width);
    header.sizeImage = static_cast<std::uint32_t>(rowStride * static_cast<std::size_t>(absHeight));

    header.xPixelsPerMeter = 0;     // Độ phân giải ngang, không dùng ở đây
    header.yPixelsPerMeter = 0;     // Độ phân giải dọc, không dùng ở đây
    header.colorsUsed = 0;     // Không dùng bảng màu
    header.colorsImportant = 0;     // Không quan trọng về màu

    image.infoHeader = header;      // Gán header vào đối tượng ảnh
    image.fileHeader.size = static_cast<std::uint32_t>(14 + 40 + header.sizeImage); // Tổng kích thước file

    const std::size_t pixelCount = static_cast<std::size_t>(width) * static_cast<std::size_t>(absHeight);
    image.data.assign(pixelCount, Pixel{});
    return image;
}

// Đọc một file BMP từ đĩa và chuyển thành cấu trúc BMPImage.
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

    // Đọc header của file BMP.
    BMPFileHeader fileHeader{};
    input.read(reinterpret_cast<char *>(&fileHeader), sizeof(fileHeader));
    if (!input || fileHeader.type != 0x4D42 || fileHeader.reserved1 != 0 || fileHeader.reserved2 != 0) {
        return false;
    }

    // Đọc kích thước DIB header: 40 cho BMP V3, 108 cho V4, 124 cho V5.
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
    // Chuyển đổi dữ liệu DIB header sang đúng kiểu phù hợp.

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

    // Lấy các thông tin cần thiết từ header để kiểm tra định dạng ảnh.
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

    // Bắt đầu đọc dữ liệu pixel từ vị trí offset trong file.
    input.seekg(fileHeader.offset, std::ios::beg);
    std::vector<std::uint8_t> rowBuffer(rowStride);
    for (std::int32_t y = 0; y < absHeight; ++y) {
        input.read(reinterpret_cast<char *>(rowBuffer.data()), rowStride);
        if (!input) {
            return false;
        }
        // Nếu height > 0, dữ liệu được lưu theo kiểu bottom-up, nên cần đảo ngược hàng khi đọc.
        // Nếu height < 0, dữ liệu đã ở dạng top-down nên giữ nguyên thứ tự.
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

// Ghi dữ liệu ảnh BMP ra file.
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
    const std::size_t rowStride =
        static_cast<std::size_t>(width) * 3 + calculatePadding(width);
    const std::size_t pixelDataSize =
        rowStride * static_cast<std::size_t>(absHeight);

    std::size_t dibSize = std::visit([](const auto &header) {
        return static_cast<std::size_t>(header.size);
    }, img.infoHeader);

    BMPFileHeader fileHeader{};
    fileHeader.type = 0x4D42;
    fileHeader.offset = static_cast<std::uint32_t>(14 + dibSize);
    fileHeader.size =
        static_cast<std::uint32_t>(fileHeader.offset + pixelDataSize);

    // Tạo một bản sao header để cập nhật kích thước dữ liệu thực tế trước khi ghi.
    auto headerCopy = img.infoHeader;
    std::visit([&headerCopy, pixelDataSize](auto &header) {
        header.sizeImage = static_cast<std::uint32_t>(pixelDataSize);
        header.size = static_cast<std::uint32_t>(header.size);
    }, headerCopy);

    output.write(reinterpret_cast<const char *>(&fileHeader),
                 sizeof(fileHeader));
    if (!output) {
        return false;
    }

    std::visit([&output](const auto &header) {
        output.write(reinterpret_cast<const char *>(&header),
                     sizeof(header));
    }, headerCopy);

    if (!output) {
        return false;
    }

    if (img.data.size() <
        static_cast<std::size_t>(width) *
        static_cast<std::size_t>(absHeight)) {
        return false;
    }

    std::vector<std::uint8_t> rowBuffer(rowStride, 0);

    for (std::int32_t y = 0; y < absHeight; ++y) {
        // Khi ghi ảnh, cần đảo ngược thứ tự hàng nếu chiều cao dương
        // để phù hợp với chuẩn BMP bottom-up.
        const std::int32_t sourceRow =
            (height > 0) ? (absHeight - 1 - y) : y;

        for (std::int32_t x = 0; x < width; ++x) {
            const std::size_t index =
                static_cast<std::size_t>(sourceRow) *
                    static_cast<std::size_t>(width) +
                static_cast<std::size_t>(x);

            const Pixel &pixel = img.data[index];
            const std::size_t offset =
                static_cast<std::size_t>(x) * 3;

            rowBuffer[offset] = pixel.blue;
            rowBuffer[offset + 1] = pixel.green;
            rowBuffer[offset + 2] = pixel.red;
        }

        output.write(reinterpret_cast<const char *>(rowBuffer.data()),
                     rowStride);

        if (!output) {
            return false;
        }
    }

    return true;
}

// Tạo tên file đầu ra bằng cách chèn chuỗi "_processed"
// trước phần mở rộng.
std::string generateOutputPath(const std::string &inputPath) {
    const std::size_t dotPosition = inputPath.find_last_of('.');

    if (dotPosition == std::string::npos) {
        return inputPath + "_processed";
    }

    return inputPath.substr(0, dotPosition) +
           "_processed" +
           inputPath.substr(dotPosition);
}

// Tính số byte padding cần thêm để mỗi hàng dữ liệu pixel
// có độ dài chia hết cho 4.

inline std::size_t calculatePadding(std::int32_t width) {
    return (4 - ((static_cast<std::size_t>(width) * 3) % 4)) % 4;
}

std::uint8_t clampColor(double value) {
    // TODO: Restrict a floating-point channel value to the valid 8-bit range.
}

Pixel getPixelSafe(const BMPImage &img, std::int32_t x, std::int32_t y) {
    // TODO:  Return the requested pixel or black when coordinates exceed image boundaries.
}