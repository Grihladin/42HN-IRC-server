#include "ParsedCommand.hpp"

ParsedCommand::ParsedCommand(std::string rawCommand,
	std::vector<std::string> arguments) : command(std::move(rawCommand)),
	args(std::move(arguments))
{
    std::cout << "ParsedCommand created with command: " << command << "\n";
}

const std::string &ParsedCommand::getCommand() const
{
	return (command);
}

const std::vector<std::string> &ParsedCommand::getArgs() const
{
	return (args);
}

size_t ParsedCommand::argCount() const
{
	return (args.size());
}
