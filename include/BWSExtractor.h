#pragma once

#include <string>
#include <optional>

class BWSExtractor {
public:
    // Extracts BWS number from a given filename string (not the path)
    static std::optional<std::string> extract(const std::string &filename);
};
