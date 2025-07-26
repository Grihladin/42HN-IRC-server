/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:53:34 by macbook           #+#    #+#             */
/*   Updated: 2025/07/26 12:37:09 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/Definitions.hpp"
#include "../../Include/IrcServer.hpp"

int IrcServer::ircCommandUser(Command &command)
{
	int		userFd;
	User	*user;

	userFd = command.getUserFd();
	user = getUserByFd(userFd);
	if (!user || !user->isAuthenticated())
	{
		std::string response = ERR_PASSWDMISMATCH();
		sendToFd(userFd, response);
		return (1);
	}
	if (user->isRegistered())
	{
		std::string response = ERR_ALREADYREGISTRED();
		sendToFd(userFd, response);
		return (1);
	}
	const std::vector<paramstruct> &params = command.getParams();
	if (params.size() < 4)
	{
		std::string response = ERR_NEEDMOREPARAMS("USER");
		sendToFd(userFd, response);
		return (1);
	}
	user->setUsername(params[0].value);
	user->setRealname(params[3].value);
	if (!user->getNickname().empty())
	{
		user->setRegistered();
		sendToFd(userFd, RPL_WELCOME(user->getNickName()));
		sendToFd(userFd, RPL_MOTDSTART("My supercool IRC server"));
		sendToFd(userFd, RPL_MOTD("Hello! You are welcome!"));
		sendToFd(userFd, RPL_ENDOFMOTD());
	}
	return (0);
}
