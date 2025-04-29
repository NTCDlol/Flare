#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <vector>
#include <variant>

/**
 * Represents a variable in the Flare language.
 * Variables in Flare have a type and a value.
 */
class Variable {
public:
    // Different variable types in Flare
    enum class Type {
        STRING,     // str
        INTEGER,    // int
        FLOAT,      // fl
        BINARY,     // bin
        LIST,       // ls
        BOOLEAN,    // act
        UNKNOWN
    };

    // Constructors
    Variable();
    Variable(const std::string& typeAndName, const std::string& value);
    
    // Get the full type and name (e.g., "str.name")
    std::string getTypeAndName() const;
    
    // Get just the name part (e.g., "name" from "str.name")
    std::string getName() const;
    
    // Get just the type part (e.g., "str" from "str.name")
    std::string getTypeString() const;
    
    // Get the type enum
    Type getType() const;
    
    // Get the value as a string
    std::string getValueAsString() const;
    
    // Set the value from a string
    void setValueFromString(const std::string& value);
    
    // Get the specific value based on type
    int getIntValue() const;
    float getFloatValue() const;
    std::string getStringValue() const;
    bool getBoolValue() const;
    std::vector<Variable> getListValue() const;
    
    // Add a value to a list variable
    void addToList(const Variable& var);
    
    // Check if the variable is of a specific type
    bool isString() const;
    bool isInteger() const;
    bool isFloat() const;
    bool isBinary() const;
    bool isList() const;
    bool isBoolean() const;

private:
    std::string m_typeAndName;  // Full type.name
    std::string m_name;         // Just the name
    Type m_type;                // Type enum
    
    // Value can be one of several types
    using ValueType = std::variant<std::string, int, float, bool, std::vector<Variable>>;
    ValueType m_value;
    
    // Helper method to determine the type from a type string
    Type typeFromString(const std::string& typeStr);
};

#endif // VARIABLE_H
