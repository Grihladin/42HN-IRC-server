#pragma once
#include <cstddef>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

class Client
{
  public:
	ParsedCommand(std::string rawCommand, std::vector<std::string> arguments);

	const std::string &getCommand() const;
	const std::vector<std::string> &getArgs() const;
	size_t argCount() const;

  private:
	std::string _NickName;
};