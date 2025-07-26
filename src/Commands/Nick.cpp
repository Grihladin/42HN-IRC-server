/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:50:32 by macbook           #+#    #+#             */
/*   Updated: 2025/07/26 11:30:45 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/Definitions.hpp"
#include "../../Include/IrcServer.hpp"

int IrcServer::ircCommandNick(Command &command)
{
	int		userFd;
	User	*user;

	userFd = command.getUserFd();
	user = getUserByFd(userFd);
	std::string nickPrefix = user
		&& !user->getNickname().empty() ? user->getNickname() : "*";
	if (!user || !user->isAuthenticated())
	{
		std::string response = ERR_PASSWDMISMATCH();
		send(userFd, response.c_str(), response.length(), 0);
		return (1);
	}
	if (command.getParams().empty())
	{
		std::string response = ERR_NONICKNAMEGIVEN();
		send(userFd, response.c_str(), response.length(), 0);
		return (1);
	}
	std::string newNick = command.getParams()[0].value;
	// Validate nickname format (RFC: must begin with a letter or special,max 9 chars, no spaces or control characters)
	if (newNick.length() > 9
		|| newNick.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-[]\\`^{}_") != std::string::npos
		|| isdigit(newNick[0]))
	{
		std::string response = ERR_ERRONEUSNICKNAME(newNick);
		send(userFd, response.c_str(), response.length(), 0);
		return (1);
	}
	if (isNicknameExist(newNick))
	{
		std::string response = ERR_NICKNAMEINUSE(newNick);
		send(userFd, response.c_str(), response.length(), 0);
		return (1);
	}
	std::string oldNick = user->getNickname();
	user->setNickname(newNick);
	if(user->isRegistered())
	{
		std::string response = RPL_WELCOME(newNick);
		send(userFd, response.c_str(), response.length(), 0);
	}
    //POSSIBLY HANDLING OF SETTING NEW NICKNAME OVER NEW ONE NEEDS TO BE HANDLED
	return (0);
}
