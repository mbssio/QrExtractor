#pragma once

#include <string>

class MuPDFConverter {
    public:
        explicit MuPDFConverter(const std::string& mutoolPath);
        bool convertFirstPage(const std::string& inputPath, const std::string& outputPath);

    private:
        std::string mutool;
};
