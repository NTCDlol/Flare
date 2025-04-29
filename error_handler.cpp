#include "error_handler.h"
#include <iostream>

ErrorHandler::ErrorHandler() {
}

ErrorHandler::~ErrorHandler() {
}

void ErrorHandler::reportError(const std::string& message, int line, const std::string& file) {
    ErrorInfo error(message, line, file);
    m_errors.push_back(error);
    
    // Print the error to stderr
    std::cerr << "ERROR: " << message;
    if (line >= 0) {
        std::cerr << " at line " << line;
    }
    if (!file.empty()) {
        std::cerr << " in file " << file;
    }
    std::cerr << std::endl;
}

void ErrorHandler::reportWarning(const std::string& message, int line, const std::string& file) {
    ErrorInfo warning(message, line, file);
    m_warnings.push_back(warning);
    
    // Print the warning to stderr
    std::cerr << "WARNING: " << message;
    if (line >= 0) {
        std::cerr << " at line " << line;
    }
    if (!file.empty()) {
        std::cerr << " in file " << file;
    }
    std::cerr << std::endl;
}

bool ErrorHandler::hasErrors() const {
    return !m_errors.empty();
}

const std::vector<ErrorInfo>& ErrorHandler::getErrors() const {
    return m_errors;
}

const std::vector<ErrorInfo>& ErrorHandler::getWarnings() const {
    return m_warnings;
}

void ErrorHandler::clear() {
    m_errors.clear();
    m_warnings.clear();
}
