/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:32:10 by macbook           #+#    #+#             */
/*   Updated: 2025/07/24 21:11:11 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <vector>
#include <optional>
#include <cstddef>
#include <iostream>
#include <optional>

struct paramstruct
{
    std::string name;
	std::string value;
};

class Command {
public:
    Command() = default;
    Command(std::string rawCommand, std::vector<struct paramstruct> arguments, int fd);
	// Command& operator=(const Command&) = default;
    const std::vector<struct paramstruct>& getParams() const;
    size_t paramCount() const;
    void setUserFd(int client_socket);
    void setParams(const std::vector<paramstruct>& params);
    void addParam(struct paramstruct& newparam);
    void setCommand(std::string newcommand);
    const std::string& getCommand(void) const;
    int getUserFd(void) const;
    static Command parse(const std::string &line);
    void setPrefix(std::string prefix);
    const std::optional<std::string>& getPrefix() const;
private:
    std::string         _prefix;
    std::string         _command;
    std::vector<struct paramstruct>  _params;
    int                 _user_fd;
};
