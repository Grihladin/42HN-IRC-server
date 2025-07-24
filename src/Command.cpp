/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:23:28 by psenko            #+#    #+#             */
/*   Updated: 2025/07/24 16:16:42 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/Command.hpp"

Command::Command(std::string rawCommand,
	std::vector<struct paramstruct> arguments, int fd) : _command(std::move(rawCommand)),
	_params(std::move(arguments))
{
	_user_fd = fd;
    std::cout << "Command created with command: " << _command << "\n";
}

const std::string &Command::getCommand() const
{
	return (_command);
}

const std::vector<struct paramstruct> &Command::getParams() const
{
	return (_params);
}

size_t Command::paramCount() const
{
	return (_params.size());
}

void Command::setCommand(std::string newcommand)
{
    _command = newcommand;
}

int Command::getUserFd(void) const
{
    return (_user_fd);
}
