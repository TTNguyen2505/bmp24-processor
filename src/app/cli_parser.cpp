#include "../../include/app/cli_parser.hpp"

#include <charconv>
#include <iostream>
#include <string>
#include <unordered_map>

const std::unordered_map<std::string, FilterType> FILTER_MAP{
        {"-grayscale", FilterType::Grayscale}, {"-sepia", FilterType::Sepia},
        {"-invert", FilterType::Invert},       {"-brightness", FilterType::Brightness},
        {"-contrast", FilterType::Contrast},   {"-saturate", FilterType::Saturate},
};

const std::unordered_map<std::string, TransformType> TRANSFORM_MAP{
        {"--translate", TransformType::Translate},
        {"--scale", TransformType::Scale},
        {"--rotate", TransformType::Rotate},
        {"--shear", TransformType::Shear},
};

/**
 * @brief Marks the command configuration as invalid.
 *
 * Sets the configuration's validity flag to false and stores the
 * corresponding error message.
 *
 * @param config Command configuration to update.
 * @param message Error message describing the failure.
 */
void fail(CommandConfig &config, const std::string &message) {
    config.isValid = false;
    config.errorMessage = message;
}

/**
 * @brief Parses a numeric command-line argument.
 *
 * Reads the next command-line argument, validates that it is a valid
 * numeric value, converts it to a double, and advances the argument index.
 * If parsing fails, the command configuration is marked as invalid and an
 * appropriate error message is stored.
 *
 * @param argc Number of command-line arguments.
 * @param argv Command-line argument array.
 * @param i Current argument index. Incremented if a value is successfully parsed.
 * @param value Output variable receiving the parsed numeric value.
 * @param config Command configuration used for error reporting.
 * @param option Option currently being parsed (used in error messages).
 * @return true if a valid numeric value was parsed; otherwise false.
 */
bool parseNumber(int argc, char *argv[], int &i, double &value, CommandConfig &config, const std::string &option) {
    if (i + 1 >= argc) {
        fail(config, "Option " + option + " requires a numeric argument.");
        return false;
    }

    if (!isNumber(argv[i + 1])) {
        fail(config, "Option " + option + " requires a valid numeric value.");
        return false;
    }

    value = std::stod(argv[++i]);
    return true;
}

/**
 * @brief Parses a color filter operation.
 *
 * Parses the numeric parameter associated with the specified filter option
 * and appends the corresponding filter operation to the command configuration.
 *
 * @param config Command configuration to update.
 * @param argc Number of command-line arguments.
 * @param argv Command-line argument array.
 * @param i Current argument index. Updated as arguments are consumed.
 * @param arg Filter option being parsed.
 * @return true if the filter was successfully parsed; otherwise false.
 */
bool parseFilter(CommandConfig &config, int argc, char *argv[], int &i, const std::string &arg) {
    auto it = FILTER_MAP.find(arg);

    if (it == FILTER_MAP.end())
        return false;

    double amount;

    if (!parseNumber(argc, argv, i, amount, config, arg))
        return false;

    config.filters.push_back({it->second, amount});

    return true;
}

/**
 * @brief Parses a geometric transformation.
 *
 * Parses the numeric parameter(s) associated with the specified
 * transformation option and appends the corresponding transformation
 * operation to the command configuration.
 *
 * Transformations accepting two parameters may also be specified with a
 * single value, in which case the value is applied to both parameters.
 *
 * @param config Command configuration to update.
 * @param argc Number of command-line arguments.
 * @param argv Command-line argument array.
 * @param i Current argument index. Updated as arguments are consumed.
 * @param arg Transformation option being parsed.
 * @return true if the transformation was successfully parsed; otherwise false.
 */
bool parseTransform(CommandConfig &config, int argc, char *argv[], int &i, const std::string &arg) {
    auto it = TRANSFORM_MAP.find(arg);

    if (it == TRANSFORM_MAP.end())
        return false;

    if (it->second == TransformType::Rotate) {
        double angle;

        if (!parseNumber(argc, argv, i, angle, config, arg))
            return false;

        config.transforms.push_back({TransformType::Rotate, angle, 0.0});

        return true;
    }

    double p1;

    if (!parseNumber(argc, argv, i, p1, config, arg))
        return false;

    double p2 = p1;

    if (i + 1 < argc && isNumber(argv[i + 1])) {
        p2 = std::stod(argv[++i]);
    }

    config.transforms.push_back({it->second, p1, p2});

    return true;
}

/**
 * @brief Parses a file path argument.
 *
 * Assigns the argument as the input or output file path, depending on
 * which field has not yet been set. If both paths are already assigned,
 * the command configuration is marked as invalid.
 *
 * @param config Command configuration to update.
 * @param arg File path argument.
 * @return true if the file path was successfully assigned; otherwise false.
 */
bool parseFileArgument(CommandConfig &config, const std::string &arg) {
    if (config.inputPath.empty()) {
        config.inputPath = arg;
        return true;
    }

    if (config.outputPath.empty()) {
        config.outputPath = arg;
        return true;
    }

    fail(config, "Unexpected argument: " + arg);

    return false;
}

CommandConfig parse(int argc, char *argv[]) {
    CommandConfig config;

    if (argc <= 1) {
        config.showHelp = true;
        return config;
    }

    for (int i = 1; i < argc; ++i) {
        std::string arg(argv[i]);

        if (arg == "-h" || arg == "--help") {
            config.showHelp = true;
            return config;
        }
    }

    for (int i = 1; i < argc && config.isValid; ++i) {
        std::string arg(argv[i]);

        if (FILTER_MAP.count(arg)) {
            if (!parseFilter(config, argc, argv, i, arg))
                break;

            continue;
        }

        if (TRANSFORM_MAP.count(arg)) {
            if (!parseTransform(config, argc, argv, i, arg))
                break;

            continue;
        }

        if (!arg.empty() && arg.front() == '-') {
            fail(config, "Unknown option: " + arg);
            break;
        }

        if (!parseFileArgument(config, arg))
            break;
    }

    if (config.isValid && config.inputPath.empty()) {
        fail(config, "No input BMP file was provided.");
    }

    return config;
}

void printHelp() {
    std::cout << "BMP24 Processor CLI\n"
              << "Usage:\n"
              << "  bmp24-processor.exe [options] <input.bmp>\n"
              << "\n"
              << "Description:\n"
              << "  Load a 24-bit BMP image, apply color filters and geometric transforms,\n"
              << "  then save the processed image.\n"
              << "\n"
              << "Input and output:\n"
              << "  <input.bmp>         Path to the source BMP file.\n"
              << "                      If omitted, the program generates a name such as\n"
              << "                      input-<timestamp>.bmp.\n"
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
              << "  bmp24-processor.exe -grayscale 0.5 input.bmp\n"
              << "  bmp24-processor.exe -invert 0.5 --rotate 90 input.bmp\n"
              << "  bmp24-processor.exe --translate 100 50 --scale 1.5 1.5 input.bmp\n"
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
