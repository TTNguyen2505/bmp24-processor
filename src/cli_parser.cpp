/**
 * @file cli_parser.cpp
 * @brief Triển khai các hàm phân tích tham số dòng lệnh và hỗ trợ giao diện CLI.
 * @details Xử lý kiểm tra tính hợp lệ của tham số đầu vào, phân tích các tùy chọn
 *          biến đổi hình học và bộ lọc màu, và hiển thị hướng dẫn sử dụng.
 */

#include "../include/cli_parser.hpp"
#include <iostream>
#include <sstream>
#include <cctype>

/**
 * @brief Kiểm tra xem một chuỗi có phải là số thực hoặc số nguyên hợp lệ hay không.
 * @details Sử dụng std::stringstream để xác minh toàn bộ nội dung chuỗi có thể
 *          chuyển đổi sang kiểu double mà không chứa ký tự không hợp lệ.
 * @param str Chuỗi đầu vào cần kiểm tra.
 * @return `true` nếu chuỗi là một giá trị số hợp lệ; `false` nếu ngược lại.
 */
[[nodiscard]]
bool isNumber(const std::string &str) {
    if (str.empty()) {
        return false;
    }
    
    std::stringstream ss(str);
    double val;
    ss >> val;
    
    // Đảm bảo chuyển đổi thành công và đã đọc hết toàn bộ chuỗi
    return !ss.fail() && ss.eof();
}

/**
 * @brief Hiển thị hướng dẫn sử dụng, các tùy chọn và các phép xử lý được hỗ trợ.
 * @details In ra định dạng chi tiết hướng dẫn CLI bao gồm cú pháp phép biến đổi hình học,
 *          tham số bộ lọc màu, các cờ đầu vào/đầu ra và ví dụ thực thi.
 */
void printHelp() {
    std::cout << "=================================================================\n";
    std::cout << "             BMP 24-BIT IMAGE PROCESSING CLI ENGINE             \n";
    std::cout << "=================================================================\n\n";
    std::cout << "CU PHAP CHUNG:\n";
    std::cout << "  ./image_processor -i <input.bmp> [-o <output.bmp>] [OPTIONS...]\n\n";
    std::cout << "THAM SO BAT BUOC / THUONG DUNG:\n";
    std::cout << "  -h, --help                Hien thi huong dan su dung nay.\n";
    std::cout << "  -i, --input <file>        Duong dan toi file BMP 24-bit dau vao.\n";
    std::cout << "  -o, --output <file>       Duong dan file dau ra (Mac dinh: tu dong tao theo ten file dau vao).\n\n";
    std::cout << "PHEP BIEN DOI HINH HOC (TRANSFORMS):\n";
    std::cout << "  --translate <tx> <ty>     Dich chuyen anh theo truc X va Y.\n";
    std::cout << "  --scale <sx> <sy>         Co co/Phong to anh theo he so sx va sy.\n";
    std::cout << "  --rotate <rad>            Xoay anh goc theta (tinh bang Radian).\n";
    std::cout << "  --shear <alpha> <beta>    Bien dang xien (shear) anh goc alpha va beta.\n\n";
    std::cout << "BO LOC MAU (FILTERS):\n";
    std::cout << "  --grayscale [amount]      Loc anh xam (amount trong [0.0, 1.0], mac dinh: 1.0).\n";
    std::cout << "  --sepia [amount]          Loc mau Sepia (amount trong [0.0, 1.0], mac dinh: 1.0).\n";
    std::cout << "  --invert [amount]         Dao nguoc mau (amount trong [0.0, 1.0], mac dinh: 1.0).\n";
    std::cout << "  --brightness <amount>     Chinh do sang (amount >= 0.0).\n";
    std::cout << "  --contrast <amount>       Chinh do tuong phan (amount >= 0.0).\n";
    std::cout << "  --saturate <amount>       Chinh do bao hoa mau (amount >= 0.0).\n\n";
    std::cout << "VI DU:\n";
    std::cout << "  ./image_processor -i input.bmp -o out.bmp --grayscale --rotate 1.57\n";
    std::cout << "  ./image_processor -i test.bmp --scale 2.0 2.0 --brightness 1.2\n";
    std::cout << "=================================================================\n";
}

/**
 * @brief Phân tích các tham số dòng lệnh thô thành đối tượng cấu hình `CommandConfig`.
 * @details Duyệt qua các tham số trong `argv`, kiểm tra tính hợp lệ của các tham số số
 *          cho phép biến đổi và bộ lọc, và đưa các thao tác vào danh sách xử lý.
 * @param argc Số lượng tham số dòng lệnh truyền vào chương trình.
 * @param argv Mảng chuỗi chứa các tham số dòng lệnh.
 * @return `CommandConfig` chứa đường dẫn, danh sách thao tác, trạng thái hợp lệ và thông báo lỗi.
 * @note Thiết lập `isValid = false` và ghi thông báo lỗi chi tiết nếu thiếu tham số
 *       hoặc gặp cờ không hợp lệ.
 */
[[nodiscard]]
CommandConfig parse(int argc, char *argv[]) {
    CommandConfig config;

    // Hiển thị trợ giúp nếu không có tham số nào được truyền vào
    if (argc <= 1) {
        config.showHelp = true;
        return config;
    }

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        // -- Cờ yêu cầu trợ giúp
        if (arg == "-h" || arg == "--help") {
            config.showHelp = true;
            return config;
        }
        // -- Đường dẫn file đầu vào
        else if (arg == "-i" || arg == "--input") {
            if (i + 1 < argc) {
                config.inputPath = argv[++i];
            } else {
                config.isValid = false;
                config.errorMessage = "Thieu duong dan file dau vao sau " + arg;
                return config;
            }
        }
        // -- Đường dẫn file đầu ra
        else if (arg == "-o" || arg == "--output") {
            if (i + 1 < argc) {
                config.outputPath = argv[++i];
            } else {
                config.isValid = false;
                config.errorMessage = "Thieu duong dan file dau ra sau " + arg;
                return config;
            }
        }
        // -- Phép biến đổi: Translate (yêu cầu 2 tham số số tx, ty)
        else if (arg == "--translate") {
            if (i + 2 < argc && isNumber(argv[i + 1]) && isNumber(argv[i + 2])) {
                double tx = std::stod(argv[++i]);
                double ty = std::stod(argv[++i]);
                config.transforms.push_back({TransformType::Translate, tx, ty});
            } else {
                config.isValid = false;
                config.errorMessage = "Tuy chon --translate yeu cau 2 tham so la so (tx, ty).";
                return config;
            }
        }
        // -- Phép biến đổi: Scale (yêu cầu 2 tham số số sx, sy)
        else if (arg == "--scale") {
            if (i + 2 < argc && isNumber(argv[i + 1]) && isNumber(argv[i + 2])) {
                double sx = std::stod(argv[++i]);
                double sy = std::stod(argv[++i]);
                config.transforms.push_back({TransformType::Scale, sx, sy});
            } else {
                config.isValid = false;
                config.errorMessage = "Tuy chon --scale yeu cau 2 tham so la so (sx, sy).";
                return config;
            }
        }
        // -- Phép biến đổi: Rotate (yêu cầu 1 tham số số theta theo Radian)
        else if (arg == "--rotate") {
            if (i + 1 < argc && isNumber(argv[i + 1])) {
                double theta = std::stod(argv[++i]);
                config.transforms.push_back({TransformType::Rotate, theta, 0.0});
            } else {
                config.isValid = false;
                config.errorMessage = "Tuy chon --rotate yeu cau 1 tham so la so (goc theta theo Radian).";
                return config;
            }
        }
        // -- Phép biến đổi: Shear (yêu cầu 2 tham số số alpha, beta)
        else if (arg == "--shear") {
            if (i + 2 < argc && isNumber(argv[i + 1]) && isNumber(argv[i + 2])) {
                double alpha = std::stod(argv[++i]);
                double beta = std::stod(argv[++i]);
                config.transforms.push_back({TransformType::Shear, alpha, beta});
            } else {
                config.isValid = false;
                config.errorMessage = "Tuy chon --shear yeu cau 2 tham so la so (alpha, beta).";
                return config;
            }
        }
        // -- Bộ lọc: Grayscale (tham số amount là tùy chọn, mặc định = 1.0)
        else if (arg == "--grayscale") {
            double amount = 1.0;
            if (i + 1 < argc && isNumber(argv[i + 1])) {
                amount = std::stod(argv[++i]);
            }
            config.filters.push_back({FilterType::Grayscale, amount});
        }
        // -- Bộ lọc: Sepia (tham số amount là tùy chọn, mặc định = 1.0)
        else if (arg == "--sepia") {
            double amount = 1.0;
            if (i + 1 < argc && isNumber(argv[i + 1])) {
                amount = std::stod(argv[++i]);
            }
            config.filters.push_back({FilterType::Sepia, amount});
        }
        // -- Bộ lọc: Invert (tham số amount là tùy chọn, mặc định = 1.0)
        else if (arg == "--invert") {
            double amount = 1.0;
            if (i + 1 < argc && isNumber(argv[i + 1])) {
                amount = std::stod(argv[++i]);
            }
            config.filters.push_back({FilterType::Invert, amount});
        }
        // -- Bộ lọc: Brightness (yêu cầu 1 tham số số)
        else if (arg == "--brightness") {
            if (i + 1 < argc && isNumber(argv[i + 1])) {
                double amount = std::stod(argv[++i]);
                config.filters.push_back({FilterType::Brightness, amount});
            } else {
                config.isValid = false;
                config.errorMessage = "Tuy chon --brightness yeu cau 1 tham so la so.";
                return config;
            }
        }
        // -- Bộ lọc: Contrast (yêu cầu 1 tham số số)
        else if (arg == "--contrast") {
            if (i + 1 < argc && isNumber(argv[i + 1])) {
                double amount = std::stod(argv[++i]);
                config.filters.push_back({FilterType::Contrast, amount});
            } else {
                config.isValid = false;
                config.errorMessage = "Tuy chon --contrast yeu cau 1 tham so la so.";
                return config;
            }
        }
        // -- Bộ lọc: Saturation (yêu cầu 1 tham số số)
        else if (arg == "--saturate") {
            if (i + 1 < argc && isNumber(argv[i + 1])) {
                double amount = std::stod(argv[++i]);
                config.filters.push_back({FilterType::Saturate, amount});
            } else {
                config.isValid = false;
                config.errorMessage = "Tuy chon --saturate yeu cau 1 tham so la so.";
                return config;
            }
        }
        // Xử lý tham số không hợp lệ
        else {
            config.isValid = false;
            config.errorMessage = "Tham so khong hop le hoac khong duoc ho tro: " + arg;
            return config;
        }
    }

    // Kiểm tra cuối cùng: Bắt buộc phải có đường dẫn file đầu vào
    if (config.inputPath.empty()) {
        config.isValid = false;
        config.errorMessage = "Chua chi dinh duong dan file dau vao! Su dung tuy chon -i hoac --input.";
    }

    return config;
}