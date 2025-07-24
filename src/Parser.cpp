/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 01:36:07 by mratke            #+#    #+#             */
/*   Updated: 2025/07/25 01:36:08 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/Command.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>

Command Command::parse(const std::string &line) {
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
    command.setPrefix(current_part.substr(1, prefix_end - 1));
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
      paramstruct trailing;
      trailing.name = "trailing";
      trailing.value = current_part.substr(1);
      command.addParam(trailing);
      break;
    }

    size_t param_end = current_part.find(' ');
    if (param_end == std::string::npos) {
      // Last parameter
      paramstruct last;
      last.name = "last";
      last.value = current_part;
      command.addParam(last);
      break;
    }

    // Middle parameter
    paramstruct last;
    last.name = "middle";
    last.value = current_part.substr(0, param_end);
    command.addParam(last);

    current_part = current_part.substr(param_end + 1);
  }

  return command;
}
