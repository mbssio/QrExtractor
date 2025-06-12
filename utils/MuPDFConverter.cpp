#include "MuPDFConverter.h"
#include <iostream>
#include <filesystem>
#include <cstdlib>

namespace fs = std::filesystem;

MuPDFConverter::MuPDFConverter(const std::string &mutoolPath) : mutool(mutoolPath) {}

bool MuPDFConverter::convertFirstPage(const std::string &inputPath, const std::string &outputPath) {
    fs::path outPath(outputPath);

    // Generate temp output path using %d for mutool
    std::string tempTemplate = outPath.parent_path().string() + "\\" + outPath.stem().string() + "_%d.jpg";
    std::string cmd = mutool + " convert -p 1 -o \"" + tempTemplate + "\" -F jpeg \"" + inputPath + "\"";

    std::cout << "Processing: " << inputPath << "\n";
    int result = std::system(cmd.c_str());
    if (result != 0) {
        std::cerr << "Failed to convert: " << inputPath << "\n";
        return false;
    }

    // Rename the output from _1.jpg to final desired name
    std::string generatedFile = outPath.parent_path().string() + "\\" + outPath.stem().string() + "_1.jpg";
    try {
        fs::rename(generatedFile, outputPath);
    } catch (const fs::filesystem_error &e) {
        std::cerr << "Failed to rename " << generatedFile << " to " << outputPath << ": " << e.what() << "\n";
        return false;
    }

    return true;
}
