#include <iostream>
#include <string>
#include <vector>

#include "../include/bmp24.hpp"
#include "../include/bmp_io.hpp"
#include "../include/cli_parser.hpp"
#include "../include/color_filter.hpp"
#include "../include/file_system.hpp"
#include "../include/geometry.hpp"
#include "../include/image.hpp"
#include "../include/matrix.hpp"
#include "../include/pipeline.hpp"
#include "../include/transform.hpp"

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
