#include "../include/ConfigManager.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

namespace fs = std::filesystem;

const std::string DEFAULT_INPUT_DIR = "C:\\pdfTest\\pdfs";
const std::string DEFAULT_OUTPUT_DIR = "C:\\pdfTest\\jpgs";

ConfigManager::ConfigManager(const std::string &filename)
    : configFile(filename), inputDir(DEFAULT_INPUT_DIR), outputDir(DEFAULT_OUTPUT_DIR) {}

void ConfigManager::createDefault() {
    std::ofstream config(configFile);
    config << "input_dir=" << DEFAULT_INPUT_DIR << "\n";
    config << "output_dir=" << DEFAULT_OUTPUT_DIR << "\n";
    std::cout << "Created default config: " << configFile << "\n";
}

bool ConfigManager::load() {
    if (!fs::exists(configFile)) {
        createDefault();
        return true;
    }

    std::ifstream config(configFile);
    if (!config.is_open()) {
        std::cerr << "Failed to open " << configFile << "\n";
        return false;
    }

    std::string line;
    while (std::getline(config, line)) {
        std::istringstream ss(line);
        std::string key, value;
        if (std::getline(ss, key, '=') && std::getline(ss, value)) {
            if (key == "input_dir")
                inputDir = value;
            else
                if (key == "output_dir")
                    outputDir = value;
        }
    }

    if (inputDir.empty() || outputDir.empty()) {
        std::cerr << "Invalid paths in " << configFile << "\n";
        return false;
    }

    return true;
}

std::string ConfigManager::getInputDir() const {
    return inputDir;
}

std::string ConfigManager::getOutputDir() const {
    return outputDir;
}
