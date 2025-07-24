#include "Command.hpp"
#include <stdexcept>
#include <iostream>
#include <sstream>

Command Command::parse(const std::string& line) {
    if (line.empty()) {
        throw std::runtime_error("Cannot parse empty line.");
    }

    Command command;
    std::string current_part = line;

    // 1. Parse Prefix
    if (current_part.rfind(":", 0) == 0) {
        size_t prefix_end = current_part.find(' ');
        if (prefix_end == std::string::npos) {
            throw std::runtime_error("Malformed message: prefix without command.");
        }
        command.setParams({{"prefix", current_part.substr(1, prefix_end - 1)}});
        current_part = current_part.substr(prefix_end + 1);
    }

    // 2. Parse Command
    size_t command_end = current_part.find(' ');
    if (command_end == std::string::npos) {
        // No parameters, the rest of the line is the command
        command.setCommand(current_part);
        return command;
    }
    command.setCommand(current_part.substr(0, command_end));
    current_part = current_part.substr(command_end + 1);

    // 3. Parse Parameters
    while (!current_part.empty()) {
        if (current_part.rfind(":", 0) == 0) {
            // Trailing parameter
            command.setParams({{"trailing", current_part.substr(1)}});
            break;
        }

        size_t param_end = current_part.find(' ');
        if (param_end == std::string::npos) {
            // Last parameter
            command.setParams({{"last", current_part}});
            break;
        }
        
        // Middle parameter
        command.setParams({{"middle", current_part.substr(0, param_end)}});
        current_part = current_part.substr(param_end + 1);
    }

    return command;
}
