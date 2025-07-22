#pragma once
#include <string>
#include <vector>
#include <optional>
#include <cstddef>
#include <iostream>

class ParsedCommand {
public:
    ParsedCommand(std::string rawCommand, std::vector<std::string> arguments);

    const std::string& getCommand() const;
    const std::vector<std::string>& getArgs() const;
    size_t argCount() const;

private:
    std::string command;
    std::vector<std::string> args;
};