#include "../include/cli_parser.hpp"
#include <string>
#include <charconv>

[[nodiscard]]
CommandConfig parse(int argc, char *argv[]) {
    CommandConfig config;

    if (argc <= 1) {
        config.showHelp = true;
        return config;
    }

    for (int i = 1; i < argc; ++i) {
        const std::string arg(argv[i]);
        if (arg == "-h" || arg == "--help") {
            config.showHelp = true;
            return config;
        }
    }

    auto fail = [&](const std::string &message) {
        config.isValid = false;
        config.errorMessage = message;
    };

    for (int i = 1; i < argc && config.isValid; ++i) {
        const std::string arg(argv[i]);

        if (arg == "-o") {
            if (i + 1 >= argc) {
                fail("Option -o requires an output file path.");
                break;
            }
            if (!config.outputPath.empty()) {
                fail("The output file path was specified more than once.");
                break;
            }
            config.outputPath = argv[++i];
            continue;
        }

        if (arg == "-grayscale" || arg == "-sepia" || arg == "-invert" ||
            arg == "-brightness" || arg == "-contrast" || arg == "-saturate") {
            if (i + 1 >= argc) {
                fail("Option " + arg + " requires 1 numeric argument.");
                break;
            }

            double amount = 0.0;
            if (!isNumber(argv[++i])) {
                fail("Option " + arg + " requires a valid numeric value.");
                break;
            }
            amount = std::stod(argv[i]);

            if (arg == "-grayscale") {
                config.filters.push_back({FilterType::Grayscale, amount});
            } else if (arg == "-sepia") {
                config.filters.push_back({FilterType::Sepia, amount});
            } else if (arg == "-invert") {
                config.filters.push_back({FilterType::Invert, amount});
            } else if (arg == "-brightness") {
                config.filters.push_back({FilterType::Brightness, amount});
            } else if (arg == "-contrast") {
                config.filters.push_back({FilterType::Contrast, amount});
            } else {
                config.filters.push_back({FilterType::Saturate, amount});
            }
            continue;
        }

        if (arg == "--translate" || arg == "--scale" || arg == "--shear") {
            if (i + 2 >= argc) {
                fail("Option " + arg + " requires 2 numeric arguments.");
                break;
            }

            if (!isNumber(argv[i + 1]) || !isNumber(argv[i + 2])) {
                fail("Option " + arg + " requires valid numeric values.");
                break;
            }

            const double p1 = std::stod(argv[++i]);
            const double p2 = std::stod(argv[++i]);

            if (arg == "--translate") {
                config.transforms.push_back({TransformType::Translate, p1, p2});
            } else if (arg == "--scale") {
                config.transforms.push_back({TransformType::Scale, p1, p2});
            } else {
                config.transforms.push_back({TransformType::Shear, p1, p2});
            }
            continue;
        }

        if (arg == "--rotate") {
            if (i + 1 >= argc) {
                fail("Option --rotate requires 1 numeric argument.");
                break;
            }

            if (!isNumber(argv[++i])) {
                fail("Option --rotate requires a valid numeric value.");
                break;
            }

            config.transforms.push_back({TransformType::Rotate, std::stod(argv[i]), 0.0});
            continue;
        }

        if (!arg.empty() && arg[0] == '-') {
            fail("Unknown option: " + arg);
            break;
        }

        if (config.inputPath.empty()) {
            config.inputPath = arg;
        } else if (config.outputPath.empty()) {
            config.outputPath = arg;
        } else {
            fail("Unexpected argument: " + arg);
            break;
        }
    }

    if (config.isValid && config.inputPath.empty()) {
        fail("No input BMP file was provided.");
    }

    return config;
}

void printHelp() {
    // TODO: Display usage instructions, supported options, parameters, examples, and file requirements.
}

bool isNumber(const std::string &str) {
    if (str.empty()) return false;

    double value;
    auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), value);

    return ec == std::errc{} && ptr == str.data() + str.size();
}
