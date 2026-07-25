#include "../include/cli_parser.hpp"

[[nodiscard]]
CommandConfig parse(int argc, char *argv[]) {
    // TODO:  Parse arguments into configuration, operations, help status, and validation errors.
    return {};
}

void printHelp() {
    // TODO: Display usage instructions, supported options, parameters, examples, and file requirements.
}

[[nodiscard]]
bool isNumber(const std::string &str) {
    for (int i = 0; i < str.length(); i++) {
        if (!std::isdigit(str[i]))
            return false;
    }
    return true;
}
