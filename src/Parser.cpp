/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 01:36:07 by mratke            #+#    #+#             */
/*   Updated: 2025/07/28 23:20:33 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/Command.hpp"
#include <sstream>

std::string cleanString(const std::string &s) {
  size_t end = s.size();
  size_t start = 0;
  while (start < end && (s[start] == ' ' || s[start] == '\t' ||
                         s[start] == '\r' || s[start] == '\n')) {
    start++;
  }
  while (end > 0 && (s[end - 1] == ' ' || s[end - 1] == '\t' ||
                     s[end - 1] == '\r' || s[end - 1] == '\n')) {
    end--;
  }
  return s.substr(start, end - start);
}

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
    std::string prefix = current_part.substr(1, prefix_end - 1);
    command.setPrefix(cleanString(prefix));
    current_part = current_part.substr(prefix_end + 1);
  }

  // 2. Parse Command
  size_t command_end = current_part.find(' ');
  if (command_end == std::string::npos) {
    // No parameters, the rest of the line is the command
    std::string cmd = current_part;
    for (size_t i = 0; i < cmd.size(); ++i) {
      cmd[i] = std::toupper(static_cast<unsigned char>(cmd[i]));
    }
    command.setCommand(cleanString(cmd));
    return command;
  }
  std::string cmd = current_part.substr(0, command_end);
  for (size_t i = 0; i < cmd.size(); ++i) {
    cmd[i] = std::toupper(static_cast<unsigned char>(cmd[i]));
  }
  command.setCommand(cleanString(cmd));
  current_part = current_part.substr(command_end + 1);

  // 3. Parse Parameters
  while (!current_part.empty()) {
    if (current_part.rfind(":", 0) == 0) {
      // Trailing parameter
      paramstruct trailing;
      trailing.name = "trailing";
      trailing.value = cleanString(current_part.substr(1));
      command.addParam(trailing);
      break;
    }

    size_t param_end = current_part.find(' ');
    if (param_end == std::string::npos) {
      // Last parameter
      paramstruct last;
      last.name = "last";
      last.value = cleanString(current_part);
      command.addParam(last);
      break;
    }

    // Middle parameter
    paramstruct middle;
    middle.name = "middle";
    middle.value = cleanString(current_part.substr(0, param_end));
    command.addParam(middle);

    current_part = current_part.substr(param_end + 1);
  }

  return command;
}
