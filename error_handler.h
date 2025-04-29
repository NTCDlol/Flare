#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <string>
#include <vector>

struct ErrorInfo {
    std::string message;
    int line;
    std::string file;
    
    ErrorInfo(const std::string& msg, int ln = -1, const std::string& f = "")
        : message(msg), line(ln), file(f) {}
};

class ErrorHandler {
public:
    ErrorHandler();
    ~ErrorHandler();

    // Report an error and optionally terminate execution
    void reportError(const std::string& message, int line = -1, const std::string& file = "");
    
    // Report a warning
    void reportWarning(const std::string& message, int line = -1, const std::string& file = "");
    
    // Check if there are any errors
    bool hasErrors() const;
    
    // Get all errors
    const std::vector<ErrorInfo>& getErrors() const;
    
    // Get all warnings
    const std::vector<ErrorInfo>& getWarnings() const;
    
    // Clear all errors and warnings
    void clear();

private:
    std::vector<ErrorInfo> m_errors;
    std::vector<ErrorInfo> m_warnings;
};

#endif // ERROR_HANDLER_H
