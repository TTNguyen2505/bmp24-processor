#include "../include/cli_parser.hpp"
#include <charconv>
#include <iostream>
#include <string>

[[nodiscard]]
CommandConfig parse(int argc, char *argv[]) {
    // TODO:  Parse arguments into configuration, operations, help status, and validation errors.
    return {};
}

void printHelp() {
    std::cout << "BMP24 Processor CLI\n"
              << "Usage:\n"
              << "  bmp24-processer.exe [options] <input.bmp>\n"
              << "  bmp24-processer.exe [options] <input.bmp> -o <output.bmp>\n"
              << "\n"
              << "Description:\n"
              << "  Load a 24-bit BMP image, apply color filters and geometric transforms,\n"
              << "  then save the processed image.\n"
              << "\n"
              << "Input and output:\n"
              << "  <input.bmp>         Path to the source BMP file.\n"
              << "  -o <output.bmp>     Write the result to a custom output file.\n"
              << "                      If omitted, the program generates a name such as\n"
              << "                      input_processed.bmp.\n"
              << "\n"
              << "General options:\n"
              << "  -h, --help          Show this help message.\n"
              << "\n"
              << "Color filters:\n"
              << "  -grayscale <amount>   Grayscale intensity in the range [0.0, 1.0].\n"
              << "  -sepia <amount>       Sepia intensity in the range [0.0, 1.0].\n"
              << "  -invert <amount>      Inversion intensity in the range [0.0, 1.0].\n"
              << "  -brightness <amount>  Brightness adjustment factor in the range [0.0, +inf).\n"
              << "  -contrast <amount>    Contrast adjustment factor in the range [0.0, +inf).\n"
              << "  -saturate <amount>    Saturation adjustment factor in the range [0.0, +inf).\n"
              << "\n"
              << "Geometric transforms:\n"
              << "  --translate <tx> <ty>  Translate along the x and y axes.\n"
              << "  --scale <sx> <sy>      Scale along the x and y axes.\n"
              << "  --rotate <theta>       Rotate by theta degrees.\n"
              << "  --shear <alpha> <beta> Shear by alpha and beta degrees.\n"
              << "\n"
              << "Examples:\n"
              << "  bmp24-processer.exe -grayscale 0.5 input.bmp\n"
              << "  bmp24-processer.exe -invert 0.5 --rotate 90 input.bmp\n"
              << "  bmp24-processer.exe --translate 100 50 --scale 1.5 1.5 input.bmp -o output.bmp\n"
              << "\n"
              << "Notes:\n"
              << "  - Filters and transforms are applied in the order they appear on the command line.\n"
              << "  - The program supports 24-bit BMP images only.\n";
}

bool isNumber(const std::string &str) {
    if (str.empty())
        return false;

    double value;
    auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), value);

    return ec == std::errc{} && ptr == str.data() + str.size();
}
