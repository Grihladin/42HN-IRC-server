/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Oper.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:51:02 by macbook           #+#    #+#             */
/*   Updated: 2025/07/26 16:14:44 by psenko           ###   ########.fr       */
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
		std::string response = ERR_NEEDMOREPARAMS("*", "OPER");
		sendToFd(userFd, response);
		return (1);
	}
	printParams(command.getParams());
	if (command.paramCount() < 2)
	{
		std::string response = ERR_NEEDMOREPARAMS("*", "OPER");
		sendToFd(userFd, response);
		return (1);
	}

	const std::vector<paramstruct> &params = command.getParams();
	std::string name = params[0].value;
	std::string password = params[1].value;

	if (password != getOperPassword())
	{
		std::string response = ERR_PASSWDMISMATCH("*");
		sendToFd(userFd, response);
		return (1);
	}

	user->setOperator(true);

	std::string response = RPL_YOUREOPER();
	sendToFd(userFd, response);
	return (0);
}