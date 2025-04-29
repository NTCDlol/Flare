#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <tuple>

class Parser {
public:
    Parser();
    ~Parser();

    // Parse a line of Flare code and return the command and its arguments
    std::tuple<std::string, std::vector<std::string>> parseLine(const std::string& line);

    // Parse a variable declaration statement (for static mode)
    std::tuple<std::string, std::string, std::string> parseVariableDeclaration(const std::string& line);

    // Check if a line is a variable declaration
    bool isVariableDeclaration(const std::string& line) const;

    // Check if a line is a memory management command
    bool isMemoryCommand(const std::string& line) const;

private:
    // Split a string by whitespace
    std::vector<std::string> splitByWhitespace(const std::string& str) const;

    // Split a string by a delimiter
    std::vector<std::string> split(const std::string& str, char delimiter) const;

    // Trim whitespace from a string
    std::string trim(const std::string& str) const;

    // Parse arguments for commands that take parenthesized arguments
    std::vector<std::string> parseParenthesizedArgs(const std::string& argsStr) const;
};

#endif // PARSER_H
