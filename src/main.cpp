#include <iostream>
#include <string>
#include <vector>

#include "app/cli_parser.hpp"
#include "app/pipeline.hpp"
#include "core/color_filter.hpp"
#include "core/image.hpp"
#include "core/transform.hpp"
#include "io/bmp24.hpp"
#include "io/bmp_io.hpp"
#include "io/file_system.hpp"
#include "math/geometry.hpp"
#include "math/matrix.hpp"

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
