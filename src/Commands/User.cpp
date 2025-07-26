/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:53:34 by macbook           #+#    #+#             */
/*   Updated: 2025/07/26 11:50:52 by psenko           ###   ########.fr       */
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
		// std::string response = RPL_WELCOME(user->getNickName());
		std::string response = RPL_MOTD("Hello!");
		sendToFd(userFd, response);
	}
	return (0);
}
