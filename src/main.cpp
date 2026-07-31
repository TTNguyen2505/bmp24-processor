#include <iostream>
#include <string>
#include <vector>

#include "../include/app/cli_parser.hpp"
#include "../include/app/pipeline.hpp"

int main(int argc, char *argv[]) {
    struct CommandConfig config = parse(argc, argv);

    if (config.showHelp) {
        printHelp();
        return 0;
    }

    if (!config.isValid) {
        std::cerr << "[CLI ERROR]: " << config.errorMessage << std::endl;
        std::cerr << "Use -h or --help to display the usage information." << std::endl;
        return 1;
    }

    return runPipeline(config) ? 0 : 1;
}
