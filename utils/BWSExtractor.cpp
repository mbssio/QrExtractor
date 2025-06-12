#include "BWSExtractor.h"
#include <regex>

std::optional<std::string> BWSExtractor::extract(const std::string& filename) {
        std::regex pattern(R"(BWS-\d{3}-\d{6}-\d{2})");
        std::smatch match;

        if (std::regex_search(filename, match, pattern)) {
                return match.str();
        }

        return std::nullopt;
}
