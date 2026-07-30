#include "app/pipeline.hpp"

#include <cstddef>
#include <iostream>
#include <string>

#include "core/color_filter.hpp"
#include "core/image.hpp"
#include "core/transform.hpp"
#include "io/bmp_io.hpp"
#include "io/file_system.hpp"

bool runPipeline(const CommandConfig &config) {
    std::string outputPath = config.outputPath.empty() ? generateOutputPath(config.inputPath) : config.outputPath;

    BMPImage inputImg;
    std::cout << "[1/4] Loading image: " << config.inputPath << "..." << std::endl;
    if (!loadBMP(config.inputPath, inputImg)) {
        std::cerr << "[ERROR]: Failed to load the BMP image or the file is invalid!" << std::endl;
        return 1;
    }

    if (getBitCount(inputImg) != 24) {
        std::cerr << "[ERROR]: Only 24-bit BMP images are supported!" << std::endl;
        return 1;
    }

    bool hasTransform = false;
    bool hasFilter = false;

    std::cout << "[2/4] Combining transformation matrices..." << std::endl;

    hasTransform = !config.transforms.empty();
    Matrix3x3 T = buildTransformMatrix(inputImg, config.transforms);

    hasFilter = !config.filters.empty();
    Matrix4x4 F = buildColorMatrix(config.filters);

    BMPImage processedImg = inputImg;

    if (hasTransform) {
        std::cout << "[3/4] Applying transformation matrix..." << std::endl;

        if (determinant(T) == 0.0) {
            std::cerr << "[ERROR]: The transformation matrix is not invertible"
                      << "(det(M) = 0). Transformation cannot be applied!" << std::endl;
            return 1;
        }

        processedImg = applyTransformMatrix(processedImg, T);
    }

    if (hasFilter) {
        std::cout << "[3/4] Applying color filter matrix..." << std::endl;

        for (std::size_t i = 0; i < processedImg.data.size(); ++i) {
            processedImg.data[i] = applyColorMatrix(F, processedImg.data[i]);
        }
    }

    std::cout << "[4/4] Saving output image to: " << outputPath << "..." << std::endl;
    if (!saveBMP(outputPath, processedImg)) {
        std::cerr << "[ERROR]: Failed to save the output image!" << std::endl;
        return 1;
    }

    std::cout << "Image processing completed successfully!" << std::endl;
    return true;
}

Matrix3x3 buildTransformMatrix(const BMPImage &image, const std::vector<TransformOperation> &operations) {
    TransformedImageBounds currentBounds = getImageBounds(image);

    Matrix3x3 T = createIdentityMatrix();

    for (const auto &op: operations) {
        Matrix3x3 currentT;

        switch (op.type) {
            case TransformType::Translate:
                currentT = createTranslationMatrix(op.param1, op.param2);
                break;

            case TransformType::Scale:
                currentT = createScaleCenterMatrix(op.param1, op.param2, currentBounds);
                break;

            case TransformType::Rotate:
                currentT = createRotationCenterMatrix(op.param1, currentBounds);
                break;

            case TransformType::Shear:
                currentT = createShearCenterMatrix(op.param1, op.param2, currentBounds);
                break;
        }

        T = currentT * T;

        currentBounds = calculateNewDimensions(currentBounds, currentT);
    }

    return T;
}

Matrix4x4 buildColorMatrix(const std::vector<FilterOperation> &operations) {
    Matrix4x4 F = {{{1.0, 0.0, 0.0, 0.0}, {0.0, 1.0, 0.0, 0.0}, {0.0, 0.0, 1.0, 0.0}, {0.0, 0.0, 0.0, 1.0}}};

    for (const auto &op: operations) {
        Matrix4x4 currentF;

        switch (op.type) {
            case FilterType::Grayscale:
                currentF = createGrayscaleMatrix(op.param1);
                break;

            case FilterType::Sepia:
                currentF = createSepiaMatrix(op.param1);
                break;

            case FilterType::Invert:
                currentF = createInvertMatrix(op.param1);
                break;

            case FilterType::Brightness:
                currentF = createBrightnessMatrix(op.param1);
                break;

            case FilterType::Contrast:
                currentF = createContrastMatrix(op.param1);
                break;

            case FilterType::Saturate:
                currentF = createSaturateMatrix(op.param1);
                break;
        }
        F = currentF * F;
    }
    return F;
}
