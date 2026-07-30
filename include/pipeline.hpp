#pragma once

#include "bmp24.hpp"
#include "cli_parser.hpp"
#include "matrix.hpp"

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

/**
 * @brief Builds a composite 3x3 transformation matrix from a sequence of operations.
 *
 * This function accumulates multiple geometric transformation operations (such as
 * translation, scaling, or rotation) applied to a BMP image and combines them
 * into a single unified 3x3 transformation matrix.
 *
 * @param[in] image The target BMPImage object, used as a reference for dimensions
 *                  or centering during transformation calculations.
 * @param[in] operations A vector of TransformOperation elements representing the
 *                       sequence of transformations to be applied.
 * @return Matrix3x3 The resulting composite 3x3 transformation matrix.
 *
 * @note Operations are typically concatenated in the order they appear in the vector.
 */
[[nodiscard]]
Matrix3x3 buildTransformMatrix(const BMPImage &image, const std::vector<TransformOperation> &operations);

/**
 * @brief Builds a composite 4x4 color transformation matrix from a list of filter operations.
 *
 * This function processes a sequence of color filter operations (such as brightness,
 * contrast, saturation, or color tint adjustments) and combines them into a single
 * unified 4x4 matrix representation for RGBA color transformation.
 *
 * @param[in] operations A vector of FilterOperation items specifying the sequence
 *                       of color filters to be concatenated.
 * @return Matrix4x4 The resulting composite 4x4 color transformation matrix.
 *
 * @note Applying a single 4x4 matrix operation to each pixel is computationally
 *       more efficient than applying multiple filter operations individually.
 */
[[nodiscard]]
Matrix4x4 buildColorMatrix(const std::vector<FilterOperation> &operations);
