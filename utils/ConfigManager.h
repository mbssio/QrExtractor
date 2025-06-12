#pragma once

#include <string>

class ConfigManager {
public:
    ConfigManager(const std::string &filename);

    bool load();

    void createDefault();

    std::string getInputDir() const;

    std::string getOutputDir() const;

private:
    std::string configFile;
    std::string inputDir;
    std::string outputDir;
};
