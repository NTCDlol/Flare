#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

class Utils {
public:
    Utils();
    ~Utils();

    // Trim whitespace from the beginning and end of a string
    std::string trim(const std::string& str) const;
    
    // Split a string by a delimiter
    std::vector<std::string> split(const std::string& str, char delimiter) const;
    
    // Join a vector of strings with a delimiter
    std::string join(const std::vector<std::string>& parts, const std::string& delimiter) const;
    
    // Check if a string starts with a prefix
    bool startsWith(const std::string& str, const std::string& prefix) const;
    
    // Check if a string ends with a suffix
    bool endsWith(const std::string& str, const std::string& suffix) const;
    
    // Convert a string to lowercase
    std::string toLower(const std::string& str) const;
    
    // Convert a string to uppercase
    std::string toUpper(const std::string& str) const;
    
    // Replace all occurrences of a substring
    std::string replaceAll(const std::string& str, const std::string& from, const std::string& to) const;
};

#endif // UTILS_H
