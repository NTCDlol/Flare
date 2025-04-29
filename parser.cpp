#include "parser.h"
#include <sstream>
#include <algorithm>
#include <cctype>

Parser::Parser() {
}

Parser::~Parser() {
}

std::tuple<std::string, std::vector<std::string>> Parser::parseLine(const std::string& line) {
    std::string trimmedLine = trim(line);
    
    // Handle variable assignments
    if (isVariableDeclaration(trimmedLine)) {
        auto [type, name, value] = parseVariableDeclaration(trimmedLine);
        std::string fullName = type + "." + name;
        return {fullName, {value}};
    }
    
    // Handle functions and commands with parenthesized arguments
    size_t openParen = trimmedLine.find('(');
    if (openParen != std::string::npos) {
        size_t closeParen = trimmedLine.find(')', openParen);
        if (closeParen != std::string::npos) {
            std::string command = trim(trimmedLine.substr(0, openParen));
            std::string argsStr = trimmedLine.substr(openParen + 1, closeParen - openParen - 1);
            std::vector<std::string> args = parseParenthesizedArgs(argsStr);
            return {command, args};
        }
    }
    
    // Handle normal commands with space-separated arguments
    std::vector<std::string> tokens = splitByWhitespace(trimmedLine);
    if (tokens.empty()) {
        return {"", {}};
    }
    
    std::string command = tokens[0];
    std::vector<std::string> args(tokens.begin() + 1, tokens.end());
    
    return {command, args};
}

std::tuple<std::string, std::string, std::string> Parser::parseVariableDeclaration(const std::string& line) {
    size_t equalsPos = line.find('=');
    if (equalsPos == std::string::npos) {
        return {"", "", ""};
    }
    
    std::string lhs = trim(line.substr(0, equalsPos));
    std::string rhs = trim(line.substr(equalsPos + 1));
    
    size_t dotPos = lhs.find('.');
    if (dotPos == std::string::npos) {
        // Dynamic mode (no explicit type)
        return {"str", lhs, rhs}; // Default to string
    }
    
    std::string type = trim(lhs.substr(0, dotPos));
    std::string name = trim(lhs.substr(dotPos + 1));
    
    return {type, name, rhs};
}

bool Parser::isVariableDeclaration(const std::string& line) const {
    // Check if the line contains an equals sign
    return line.find('=') != std::string::npos;
}

bool Parser::isMemoryCommand(const std::string& line) const {
    std::string trimmedLine = trim(line);
    return trimmedLine.find("mem(") == 0 || 
           trimmedLine.find("virmem(") == 0 || 
           trimmedLine.find("frmem(") == 0;
}

std::vector<std::string> Parser::splitByWhitespace(const std::string& str) const {
    std::vector<std::string> tokens;
    std::istringstream iss(str);
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

std::vector<std::string> Parser::split(const std::string& str, char delimiter) const {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(trim(token));
    }
    return tokens;
}

std::string Parser::trim(const std::string& str) const {
    auto start = std::find_if_not(str.begin(), str.end(), [](unsigned char c) {
        return std::isspace(c);
    });
    
    auto end = std::find_if_not(str.rbegin(), str.rend(), [](unsigned char c) {
        return std::isspace(c);
    }).base();
    
    return (start < end) ? std::string(start, end) : std::string();
}

std::vector<std::string> Parser::parseParenthesizedArgs(const std::string& argsStr) const {
    std::vector<std::string> args;
    std::string currentArg;
    bool inQuotes = false;
    int nestedParenCount = 0;
    
    for (size_t i = 0; i < argsStr.size(); ++i) {
        char c = argsStr[i];
        
        if (c == '"') {
            inQuotes = !inQuotes;
            currentArg += c;
        }
        else if (c == '(' && !inQuotes) {
            nestedParenCount++;
            currentArg += c;
        }
        else if (c == ')' && !inQuotes) {
            nestedParenCount--;
            currentArg += c;
        }
        else if (c == ',' && !inQuotes && nestedParenCount == 0) {
            args.push_back(trim(currentArg));
            currentArg.clear();
        }
        else {
            currentArg += c;
        }
    }
    
    if (!currentArg.empty()) {
        args.push_back(trim(currentArg));
    }
    
    return args;
}
