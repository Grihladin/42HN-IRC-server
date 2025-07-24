/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:23:28 by psenko            #+#    #+#             */
/*   Updated: 2025/07/24 11:24:23 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/Command.hpp"

Command::Command(std::string rawCommand,
	std::vector<Param> arguments) : command(std::move(rawCommand)),
	params(std::move(arguments))
{
    std::cout << "Command created with command: " << command << "\n";
}

const std::string &Command::getCommand() const
{
	return (command);
}

const std::vector<Param> &Command::getParams() const
{
	return (params);
}

size_t Command::paramCount() const
{
	return (params.size());
}

void Command::setCommand(std::string newcommand)
{
    command = newcommand;
}