#include "../include/file_system.hpp"

#include <chrono>
#include <filesystem>

std::string generateOutputPath(const std::string &inputPath) {
    namespace fs = std::filesystem;

    const auto now = std::chrono::system_clock::now();
    const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();

    const fs::path path(inputPath);
    const fs::path parentDir = path.parent_path();
    const std::string stem = path.stem().string();
    const std::string extension = path.extension().string();

    const std::string newFilename = stem + "-" + std::to_string(ms) + extension;

    return parentDir.empty() ? newFilename : (parentDir / newFilename).string();
}