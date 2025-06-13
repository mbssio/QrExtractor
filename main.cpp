#include <iostream>
#include <filesystem>
#include <limits>
#include "include/ConfigManager.h"
#include "include/MuPDFConverter.h"
#include "include/BWSExtractor.h"

namespace fs = std::filesystem;

const std::string CONFIG_FILE = "config.ini";
const std::string MUTOOL_PATH = "mupdf\\mutool.exe";

int main() {
    ConfigManager config(CONFIG_FILE);
    if (!config.load())
        return 1;

    std::string inputDir = config.getInputDir();
    std::string outputDir = config.getOutputDir();

    if (!fs::exists(inputDir)) {
        std::cerr << "Input directory does not exist: " << inputDir << "\n";
        return 1;
    }

    fs::create_directories(outputDir);
    MuPDFConverter converter(MUTOOL_PATH);

    for (const auto &entry: fs::directory_iterator(inputDir)) {
        if (entry.path().extension() == ".pdf") {
            std::string pdfPath = entry.path().string();
            std::string fileName = entry.path().stem().string();

            auto bwsNumber = BWSExtractor::extract(fileName);
            if (bwsNumber.has_value()) {
                std::string outputPath = outputDir + "\\" + bwsNumber.value() + ".jpg";
                converter.convertFirstPage(pdfPath, outputPath);
            } else {
                std::cerr << "No BWS number found in: " << fileName << "\n";
            }
        }
    }

    std::cout << "\nFertig!";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    return 0;
}
