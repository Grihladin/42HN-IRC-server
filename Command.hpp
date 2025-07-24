/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:59:57 by mratke            #+#    #+#             */
/*   Updated: 2025/07/24 19:03:12 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <cstddef>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

struct paramstruct {
  std::string name;
  std::string value;
};

class Command {
public:
  Command() = default;
  Command(std::string rawCommand, std::vector<struct paramstruct> arguments,
          int fd);
  // Command& operator=(const Command&) = default;
  const std::vector<struct paramstruct> &getParams() const;
  size_t paramCount() const;
  void setUserFd(int client_socket);
  void setParams(const std::vector<paramstruct> &params);
  void setCommand(std::string newcommand);
  void setPrefix(std::string prefix);
  const std::optional<std::string>& getPrefix() const;
  void addParam(struct paramstruct &newparam);
  const std::string &getCommand(void) const;
  int getUserFd(void) const;
  static Command parse(const std::string &line);

private:
  std::optional<std::string> _prefix;
  std::string _command;
  std::vector<struct paramstruct> _params;
  int _user_fd;
};
