#include "../include/cli_parser.hpp"
#include <string>
#include <charconv>

[[nodiscard]]
CommandConfig parse(int argc, char *argv[]) {
    // TODO:  Parse arguments into configuration, operations, help status, and validation errors.
    return {};
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