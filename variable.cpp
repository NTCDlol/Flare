#include "variable.h"
#include <sstream>
#include <algorithm>
#include <cctype>

Variable::Variable() : m_typeAndName("unknown"), m_name("unknown"), m_type(Type::UNKNOWN) {
    m_value = std::string("");
}

Variable::Variable(const std::string& typeAndName, const std::string& value) 
    : m_typeAndName(typeAndName) {
    
    // Extract the name part (after the dot)
    size_t dotPos = typeAndName.find('.');
    if (dotPos != std::string::npos && dotPos + 1 < typeAndName.length()) {
        m_name = typeAndName.substr(dotPos + 1);
    } else {
        m_name = typeAndName;
    }
    
    // Extract the type part (before the dot)
    std::string typeStr;
    if (dotPos != std::string::npos) {
        typeStr = typeAndName.substr(0, dotPos);
    } else {
        typeStr = "str"; // Default to string if no type specified
    }
    
    m_type = typeFromString(typeStr);
    
    // Set the value based on the type
    setValueFromString(value);
}

std::string Variable::getTypeAndName() const {
    return m_typeAndName;
}

std::string Variable::getName() const {
    return m_name;
}

std::string Variable::getTypeString() const {
    size_t dotPos = m_typeAndName.find('.');
    if (dotPos != std::string::npos) {
        return m_typeAndName.substr(0, dotPos);
    }
    
    // If there's no dot, return a default based on the type
    switch (m_type) {
        case Type::STRING: return "str";
        case Type::INTEGER: return "int";
        case Type::FLOAT: return "fl";
        case Type::BINARY: return "bin";
        case Type::LIST: return "ls";
        case Type::BOOLEAN: return "act";
        default: return "unknown";
    }
}

Variable::Type Variable::getType() const {
    return m_type;
}

std::string Variable::getValueAsString() const {
    if (std::holds_alternative<std::string>(m_value)) {
        return std::get<std::string>(m_value);
    }
    else if (std::holds_alternative<int>(m_value)) {
        return std::to_string(std::get<int>(m_value));
    }
    else if (std::holds_alternative<float>(m_value)) {
        return std::to_string(std::get<float>(m_value));
    }
    else if (std::holds_alternative<bool>(m_value)) {
        return std::get<bool>(m_value) ? "true" : "false";
    }
    else if (std::holds_alternative<std::vector<Variable>>(m_value)) {
        std::stringstream ss;
        ss << "[";
        const auto& list = std::get<std::vector<Variable>>(m_value);
        for (size_t i = 0; i < list.size(); ++i) {
            ss << list[i].getValueAsString();
            if (i < list.size() - 1) {
                ss << ", ";
            }
        }
        ss << "]";
        return ss.str();
    }
    
    return "";
}

void Variable::setValueFromString(const std::string& value) {
    switch (m_type) {
        case Type::STRING: {
            // Remove quotes if present
            if (value.size() >= 2 && value.front() == '"' && value.back() == '"') {
                m_value = value.substr(1, value.size() - 2);
            } else {
                m_value = value;
            }
            break;
        }
        case Type::INTEGER: {
            try {
                m_value = std::stoi(value);
            } catch (...) {
                m_value = 0;
            }
            break;
        }
        case Type::FLOAT: {
            try {
                m_value = std::stof(value);
            } catch (...) {
                m_value = 0.0f;
            }
            break;
        }
        case Type::BINARY: {
            // Handle binary values (hexadecimal, etc.)
            try {
                // Assuming hexadecimal format (0xNNNN)
                if (value.substr(0, 2) == "0x") {
                    m_value = std::stoi(value.substr(2), nullptr, 16);
                } else {
                    m_value = std::stoi(value);
                }
            } catch (...) {
                m_value = 0;
            }
            break;
        }
        case Type::BOOLEAN: {
            std::string lowerValue = value;
            std::transform(lowerValue.begin(), lowerValue.end(), lowerValue.begin(),
                           [](unsigned char c) { return std::tolower(c); });
            
            m_value = (lowerValue == "true" || lowerValue == "1");
            break;
        }
        case Type::LIST: {
            // Initialize an empty list
            m_value = std::vector<Variable>();
            // In a full implementation, we would parse the string to extract list elements
            break;
        }
        default:
            m_value = std::string(value);
            break;
    }
}

int Variable::getIntValue() const {
    if (std::holds_alternative<int>(m_value)) {
        return std::get<int>(m_value);
    }
    return 0;
}

float Variable::getFloatValue() const {
    if (std::holds_alternative<float>(m_value)) {
        return std::get<float>(m_value);
    }
    return 0.0f;
}

std::string Variable::getStringValue() const {
    if (std::holds_alternative<std::string>(m_value)) {
        return std::get<std::string>(m_value);
    }
    return "";
}

bool Variable::getBoolValue() const {
    if (std::holds_alternative<bool>(m_value)) {
        return std::get<bool>(m_value);
    }
    return false;
}

std::vector<Variable> Variable::getListValue() const {
    if (std::holds_alternative<std::vector<Variable>>(m_value)) {
        return std::get<std::vector<Variable>>(m_value);
    }
    return std::vector<Variable>();
}

void Variable::addToList(const Variable& var) {
    if (m_type == Type::LIST) {
        if (std::holds_alternative<std::vector<Variable>>(m_value)) {
            std::get<std::vector<Variable>>(m_value).push_back(var);
        } else {
            // Initialize the list if it's not already one
            std::vector<Variable> list;
            list.push_back(var);
            m_value = list;
        }
    }
}

bool Variable::isString() const {
    return m_type == Type::STRING;
}

bool Variable::isInteger() const {
    return m_type == Type::INTEGER;
}

bool Variable::isFloat() const {
    return m_type == Type::FLOAT;
}

bool Variable::isBinary() const {
    return m_type == Type::BINARY;
}

bool Variable::isList() const {
    return m_type == Type::LIST;
}

bool Variable::isBoolean() const {
    return m_type == Type::BOOLEAN;
}

Variable::Type Variable::typeFromString(const std::string& typeStr) {
    if (typeStr == "str") return Type::STRING;
    if (typeStr == "int") return Type::INTEGER;
    if (typeStr == "fl") return Type::FLOAT;
    if (typeStr == "bin") return Type::BINARY;
    if (typeStr == "ls") return Type::LIST;
    if (typeStr == "act") return Type::BOOLEAN;
    
    // Default to string for unknown types
    return Type::STRING;
}
