#pragma once

#include <string>
#include <vector>

/**
 * @enum TransformType
 * @brief Enumerates all supported geometric transformations.
 */
enum class TransformType { Translate, Scale, Rotate, Shear };

/**
 * @enum FilterType
 * @brief Enumerates all supported color filters.
 */
enum class FilterType { Grayscale, Sepia, Invert, Brightness, Contrast, Saturate };

/**
 * @struct TransformOperation
 * @brief Represents a single geometric transformation.
 */
struct TransformOperation {
    TransformType type;
    double param1{0.0};
    double param2{0.0};
};

/**
 * @struct FilterOperation
 * @brief Represents a single color filter.
 */
struct FilterOperation {
    FilterType type;
    double param1{0.0};
};

/**
 * @struct CommandConfig
 * @brief Stores the complete configuration parsed from the command line (CLI).
 */
struct CommandConfig {
    std::string inputPath;
    std::string outputPath;

    std::vector<TransformOperation> transforms;
    std::vector<FilterOperation> filters;

    bool showHelp{false};
    bool isValid{true};
    std::string errorMessage;
};

/**
 * @brief Parses command-line arguments.
 *
 * @param argc Number of command-line arguments.
 * @param argv Command-line argument array.
 * @return Parsed command configuration.
 */
[[nodiscard]]
CommandConfig parse(int argc, char *argv[]);

/**
 * @brief Prints the program usage instructions.
 */
void printHelp();

/**
 * @brief Checks whether a string represents a valid number.
 *
 * @param str Input string.
 * @return true if the string is numeric; otherwise false.
 */
[[nodiscard]]
bool isNumber(const std::string &str);
