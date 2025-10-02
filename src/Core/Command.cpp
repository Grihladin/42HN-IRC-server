/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:23:28 by psenko            #+#    #+#             */
/*   Updated: 2025/10/02 17:03:15 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Command.hpp"

Command::Command(std::string rawCommand,
                 std::vector<struct paramstruct> arguments, int fd)
    : _command(std::move(rawCommand)), _params(std::move(arguments)) {
  _user_fd = fd;
  std::cout << "Command created with command: " << _command << "\n";
}

const std::string &Command::getCommand() const { return (_command); }

const std::vector<struct paramstruct> &Command::getParams() const {
  return (_params);
}

size_t Command::paramCount() const { return (_params.size()); }

void Command::setCommand(std::string newcommand) { _command = newcommand; }

int Command::getUserFd(void) const { return (_user_fd); }

void Command::setParams(const std::vector<paramstruct> &params) {
  _params = params;
}

void Command::setUserFd(int client_socket) { _user_fd = client_socket; }

void Command::addParam(struct paramstruct &newparam) {
  _params.push_back(newparam);
}

void Command::setPrefix(std::string prefix) { _prefix = prefix; }

const std::optional<std::string> &Command::getPrefix() const { return _prefix; }

std::string Command::getRawCommand() const { return (_raw_command); }

void Command::setRawCommand(std::string rawCommand) {
  _raw_command = rawCommand;
}
