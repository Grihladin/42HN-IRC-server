/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServerParser.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 10:56:53 by psenko            #+#    #+#             */
/*   Updated: 2025/07/24 23:42:21 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/IrcServer.hpp"
#include "../Include/Command.hpp"

const Command IrcServer::commandParser(std::string rawdata, int client_socket)
{
	Command newcommand = Command::parse(rawdata);
	newcommand.setUserFd(client_socket);
	std::cout << "DEBUG: Raw data received by parser: '" << rawdata << "'" << std::endl;
	std::cout << "DEBUG: Parsed command: '" << newcommand.getCommand() << "'" << std::endl;
	for (const auto& param : newcommand.getParams()) {
		std::cout << "DEBUG: Param name: '" << param.name << "', value: '" << param.value << "'" << std::endl;
	}
	
	return (newcommand);
}