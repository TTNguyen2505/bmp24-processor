#include <iostream>
#include <string>
#include <vector>

#include "../include/app/cli_parser.hpp"
#include "../include/app/pipeline.hpp"
#include "../include/core/color_filter.hpp"
#include "../include/core/image.hpp"
#include "../include/core/transform.hpp"
#include "../include/io/bmp24.hpp"
#include "../include/io/bmp_io.hpp"
#include "../include/io/file_system.hpp"
#include "../include/math/geometry.hpp"
#include "../include/math/matrix.hpp"

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
