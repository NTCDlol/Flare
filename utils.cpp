#include "utils.h"
#include <algorithm>
#include <sstream>
#include <cctype>

Utils::Utils() {
}

Utils::~Utils() {
}

std::string Utils::trim(const std::string& str) const {
    auto start = std::find_if_not(str.begin(), str.end(), [](unsigned char c) {
        return std::isspace(c);
    });
    
    auto end = std::find_if_not(str.rbegin(), str.rend(), [](unsigned char c) {
        return std::isspace(c);
    }).base();
    
    return (start < end) ? std::string(start, end) : std::string();
}

std::vector<std::string> Utils::split(const std::string& str, char delimiter) const {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(trim(token));
    }
    return tokens;
}

std::string Utils::join(const std::vector<std::string>& parts, const std::string& delimiter) const {
    if (parts.empty()) {
        return "";
    }
    
    std::ostringstream result;
    result << parts[0];
    
    for (size_t i = 1; i < parts.size(); ++i) {
        result << delimiter << parts[i];
    }
    
    return result.str();
}

bool Utils::startsWith(const std::string& str, const std::string& prefix) const {
    return str.size() >= prefix.size() && str.substr(0, prefix.size()) == prefix;
}

bool Utils::endsWith(const std::string& str, const std::string& suffix) const {
    return str.size() >= suffix.size() && str.substr(str.size() - suffix.size()) == suffix;
}

std::string Utils::toLower(const std::string& str) const {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return result;
}

std::string Utils::toUpper(const std::string& str) const {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::toupper(c); });
    return result;
}

std::string Utils::replaceAll(const std::string& str, const std::string& from, const std::string& to) const {
    std::string result = str;
    size_t startPos = 0;
    while ((startPos = result.find(from, startPos)) != std::string::npos) {
        result.replace(startPos, from.length(), to);
        startPos += to.length();
    }
    return result;
}
