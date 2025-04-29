#include <iostream>
#include <string>
#include <fstream>
#include "flare_interpreter.h"

void printUsage() {
    std::cout << "Usage: flare_interpreter [options] [script_file]" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  --help, -h     Display this help message" << std::endl;
    std::cout << "  --version, -v  Display version information" << std::endl;
    std::cout << "  --exec, -e     Execute a single line of Flare code" << std::endl;
    std::cout << std::endl;
    std::cout << "Examples:" << std::endl;
    std::cout << "  flare_interpreter script.flrs" << std::endl;
    std::cout << "  flare_interpreter -e \"str.video++ = \\\"Hello\\\"\"" << std::endl;
}

void printVersion(const FlareInterpreter& interpreter) {
    std::cout << "Flare Interpreter version " << interpreter.getVersion() << std::endl;
    std::cout << "Built with C++ " << __cplusplus << std::endl;
}

int runInteractive(FlareInterpreter& interpreter) {
    std::cout << "Flare Interpreter version " << interpreter.getVersion() << std::endl;
    std::cout << "Type 'exit' to quit, 'help' for help" << std::endl;
    
    std::string line;
    while (true) {
        std::cout << "flare> ";
        std::getline(std::cin, line);
        
        if (line == "exit" || line == "quit") {
            break;
        } else if (line == "help") {
            std::cout << "Available commands:" << std::endl;
            std::cout << "  exit, quit - Exit the interpreter" << std::endl;
            std::cout << "  help - Display this help message" << std::endl;
            std::cout << "  version - Display version information" << std::endl;
            std::cout << "  Any valid Flare command" << std::endl;
        } else if (line == "version") {
            printVersion(interpreter);
        } else if (!line.empty()) {
            interpreter.loadScriptFromString(line);
            interpreter.run();
        }
    }
    
    return 0;
}

int main(int argc, char** argv) {
    FlareInterpreter interpreter;
    if (!interpreter.initialize()) {
        std::cerr << "Failed to initialize the Flare interpreter" << std::endl;
        return 1;
    }
    
    if (argc < 2) {
        // No arguments provided, start interactive mode
        return runInteractive(interpreter);
    }
    
    std::string arg1 = argv[1];
    if (arg1 == "--help" || arg1 == "-h") {
        printUsage();
        return 0;
    } else if (arg1 == "--version" || arg1 == "-v") {
        printVersion(interpreter);
        return 0;
    } else if (arg1 == "--exec" || arg1 == "-e") {
        if (argc < 3) {
            std::cerr << "Error: No code provided for execution" << std::endl;
            printUsage();
            return 1;
        }
        
        std::string code = argv[2];
        interpreter.loadScriptFromString(code);
        if (!interpreter.run()) {
            return 1;
        }
        
        return 0;
    } else {
        // Assume arg1 is a script file
        if (!interpreter.loadScript(arg1)) {
            std::cerr << "Error: Could not load script file: " << arg1 << std::endl;
            return 1;
        }
        
        if (!interpreter.run()) {
            return 1;
        }
        
        return 0;
    }
}
