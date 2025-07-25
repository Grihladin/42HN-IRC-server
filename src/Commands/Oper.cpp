/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Oper.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:51:02 by macbook           #+#    #+#             */
/*   Updated: 2025/07/25 18:26:51 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/Definitions.hpp"
#include "../../Include/IrcServer.hpp"

int IrcServer::ircCommandOper(Command &command)
{
	int userFd = command.getUserFd();
	User *user = getUserByFd(userFd);

	if (!user || !user->isRegistered())
	{
		std::string response = ERR_NEEDMOREPARAMS("OPER");
		send(userFd, response.c_str(), response.length(), 0);
		return (1);
	}

	if (command.paramCount() < 2)
	{
		std::string response = ERR_NEEDMOREPARAMS("OPER");
		send(userFd, response.c_str(), response.length(), 0);
		return (1);
	}

	const std::vector<paramstruct> &params = command.getParams();
	std::string name = params[0].value;
	std::string password = params[1].value;

	if (password != getOperPassword())
	{
		std::string response = ERR_PASSWDMISMATCH;
		send(userFd, response.c_str(), response.length(), 0);
		return (1);
	}

	user->setOperator(true);

	std::string response = RPL_YOUREOPER(user->getNickName());
	send(userFd, response.c_str(), response.length(), 0);

	return (0);
}