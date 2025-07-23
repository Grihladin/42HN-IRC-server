#include "../Include/Command.hpp"

Command::Command(std::string rawCommand,
	std::vector<std::string> arguments) : command(std::move(rawCommand)),
	args(std::move(arguments))
{
    std::cout << "Command created with command: " << command << "\n";
}

const std::string &Command::getCommand() const
{
	return (command);
}

const std::vector<std::string> &Command::getArgs() const
{
	return (args);
}

size_t Command::argCount() const
{
	return (args.size());
}
