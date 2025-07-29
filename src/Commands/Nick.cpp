/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:50:32 by macbook           #+#    #+#             */
/*   Updated: 2025/07/29 19:37:11 by auplisas         ###   ########.fr       */
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
		&& !user->getNickName().empty() ? user->getNickName() : "*";
	if (!user || !user->isAuthenticated())
	{
		std::string response = ERR_PASSWDMISMATCH("*");
		sendToFd(userFd, response);
		return (1);
	}
	if (command.getParams().empty())
	{
		std::string response = ERR_NONICKNAMEGIVEN("*");
		sendToFd(userFd, response);
		return (1);
	}
	std::string newNick = command.getParams()[0].value;
	// Validate nickname format (RFC: must begin with a letter or special,max 9 chars, no spaces or control characters)
	if (newNick.length() > 9
		|| newNick.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-[]\\`^{}_") != std::string::npos
		|| isdigit(newNick[0]))
	{
		std::string response = ERR_ERRONEUSNICKNAME("*", newNick);
		sendToFd(userFd, response);
		return (1);
	}
	if (isNicknameExist(newNick))
	{
		std::string response = ERR_NICKNAMEINUSE("*", newNick);
		sendToFd(userFd, response);
		return (1);
	}
	std::string oldNick = user->getNickName();
	user->setNickname(newNick);
	if(user->isRegistered())
	{
		std::cout << "realname: '" << user->getRealName() << "'" << std::endl;
		connectIsSuccesfull(getUserByFd(userFd));
	}
    //POSSIBLY HANDLING OF SETTING NEW NICKNAME OVER NEW ONE NEEDS TO BE HANDLED
	return (0);
}
