#pragma once

#include "cli_parser.hpp"

/**
 * @brief Executes the complete image processing pipeline.
 *
 * The pipeline performs:
 * 1. Load BMP image.
 * 2. Build transformation matrix.
 * 3. Build color filter matrix.
 * 4. Apply transformations.
 * 5. Save output image.
 *
 * @param config Parsed command line configuration.
 * @return `true` if processing succeeds.
 * @return `false` if any step fails.
 */
[[nodiscard]]
bool runPipeline(const CommandConfig &config);