/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:51:58 by macbook           #+#    #+#             */
/*   Updated: 2025/07/25 10:32:34 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/Definitions.hpp"
#include "../../Include/IrcServer.hpp"

int IrcServer::ircCommandPass(Command &command)
{
	std::string response;
	std::string currentPassword = getPassword();
	if (command.getParams().empty())
	{
		response = ERR_NEEDMOREPARAMS("PASS");
		send(command.getUserFd(), response.c_str(), response.length(), 0);
		return (0);
	}

	User *user = getUserByFd(command.getUserFd());
	std::string receivedPassword = command.getParams()[0].value;
	if (user && user->isRegistered())
	{
		response = ERR_ALREADYREGISTRED;
		send(command.getUserFd(), response.c_str(), response.length(), 0);
		return (0);
	}
	if (currentPassword == receivedPassword)
	{
		addUser(command.getUserFd());
		getUserByFd(command.getUserFd())->setAuthenticated();
		return (0);
	}
	else
	{
		response = ERR_PASSWDMISMATCH;
		send(command.getUserFd(), response.c_str(), response.length(), 0);
		deleteUser(command.getUserFd());
		return (0);
	}
}