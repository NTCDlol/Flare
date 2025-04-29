#ifndef FLARE_INTERPRETER_H
#define FLARE_INTERPRETER_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <fstream>
#include <iostream>
#include <functional>
#include <stack>
#include <dlfcn.h> // For dynamic library loading

#include "variable.h"
#include "memory_manager.h"
#include "parser.h"
#include "error_handler.h"
#include "utils.h"

// Struct to store a function definition
struct FunctionDefinition {
    std::string name;
    std::vector<std::string> parameters;
    std::vector<std::string> body;
};

// Struct to store FlameMemory object (for dynamic mode)
struct FlameMemory {
    std::string name;
    size_t size;
    std::map<std::string, Variable> data;
};

// Struct to store library information
struct Library {
    std::string name;
    void* handle;
    std::map<std::string, void*> functions;
    bool isLoaded;
};

class FlareInterpreter {
public:
    FlareInterpreter();
    ~FlareInterpreter();

    // Initialize the interpreter
    bool initialize();

    // Load a Flare script from file
    bool loadScript(const std::string& filename);

    // Load a Flare script from string
    bool loadScriptFromString(const std::string& script);

    // Run the loaded script
    bool run();

    // Get the version of the interpreter
    std::string getVersion() const;

    // Add a built-in function
    void addBuiltInFunction(const std::string& name, std::function<Variable(const std::vector<Variable>&)> func);

private:
    std::string m_version;
    bool m_isDynamicMode;
    std::string m_script;
    std::vector<std::string> m_scriptLines;
    size_t m_currentLine;
    bool m_isRunning;

    // Components of the interpreter
    std::unique_ptr<MemoryManager> m_memoryManager;
    std::unique_ptr<Parser> m_parser;
    std::unique_ptr<ErrorHandler> m_errorHandler;
    std::unique_ptr<Utils> m_utils;

    // Global variables
    std::map<std::string, Variable> m_globalVariables;
    
    // Local variables (for function calls)
    std::stack<std::map<std::string, Variable>> m_localVariables;
    
    // User-defined functions
    std::map<std::string, FunctionDefinition> m_userFunctions;
    
    // Call stack for function calls
    std::stack<size_t> m_callStack;
    
    // FlameMemory containers (for dynamic mode)
    std::map<std::string, FlameMemory> m_flameMemory;

    // Built-in functions
    std::map<std::string, std::function<Variable(const std::vector<Variable>&)>> m_builtInFunctions;
    
    // Loaded libraries
    std::map<std::string, Library> m_libraries;

    // Set up built-in functions
    void setupBuiltInFunctions();
    
    // Library management functions
    bool loadLibrary(const std::string& name, const std::string& path);
    bool unloadLibrary(const std::string& name);
    void* getLibraryFunction(const std::string& libName, const std::string& funcName);
    bool callLibraryFunction(const std::string& libName, const std::string& funcName, const std::vector<Variable>& args, Variable& result);

    // Process a single line of code
    bool processLine(const std::string& line);

    // Execute a command
    bool executeCommand(const std::string& command, const std::vector<std::string>& args);
    
    // Process control structures
    bool processIfStatement(const std::string& line);
    bool processElseStatement(const std::string& line);
    bool processForLoop(const std::string& line);
    bool processWhileLoop(const std::string& line);
    bool processFunction(const std::string& line);
    bool processFunctionCall(const std::string& name, const std::vector<std::string>& args);
    
    // Evaluate expressions
    Variable evaluateExpression(const std::string& expr);
    bool evaluateCondition(const std::string& condition);
    
    // Dynamic mode functions
    bool processDynamicMode();
    bool processFlameMemory(const std::string& command, const std::vector<std::string>& args);
    Variable processInput(); // Process user input for interactive scripts

    // Register core variables
    void registerCoreVariables();
    
    // Get a variable value (checks local scope first, then global)
    Variable getVariable(const std::string& name);
    
    // Set a variable value (in current scope)
    void setVariable(const std::string& name, const Variable& value);
};

#endif // FLARE_INTERPRETER_H
