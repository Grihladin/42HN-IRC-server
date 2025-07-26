/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 13:42:52 by mratke            #+#    #+#             */
/*   Updated: 2025/07/26 14:15:23 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/IrcServer.hpp"
#include "../../Include/User.hpp"

int IrcServer::ircCommandPing(Command &command)
{
	User *user = getUserByFd(command.getUserFd());
	if (user == NULL)
	{
		std::cout << "Error: User not found for fd: " << command.getUserFd() << std::endl;
		return (1);
	}
	const std::vector<paramstruct> &params = command.getParams();
	if (params.empty())
	{
		std::cout << "Error: PING command requires a parameter." << std::endl;
		return (1);
	}
	std::string pong_response = "PONG " + params[0].value + "\r\n";
	sendToFd(command.getUserFd(), pong_response);
	return (0);
}
