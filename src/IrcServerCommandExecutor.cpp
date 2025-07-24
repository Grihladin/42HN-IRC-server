/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServerCommandExecutor.cpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:11:44 by psenko            #+#    #+#             */
/*   Updated: 2025/07/25 02:20:50 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/IrcServer.hpp"
#include "../Include/Definitions.hpp"

void IrcServer::commandExecutor(Command &command)
{
	bool	matched;
	User	*user;
	int		fd;

	matched = false;
	for (int nn = 0; nn < COMMANDS_COUNT; nn++)
	{
		if (irccommands[nn] == command.getCommand())
		{
			(this->*executors[nn])(command);
			matched = true;
			break ;
		}
	}
	if (!matched)
	{
		fd = command.getUserFd();
		if (fd >= 0)
		{
			user = getUserByFd(fd);
			std::string nick = "*";
			if (user)
			{
				nick = user->getNickName();
				if (nick.empty())
					nick = "*";
			}
			std::string cmd = command.getCommand();
			std::string response = ERR_UNKNOWNCOMMAND(nick, cmd);
			send(fd, response.c_str(), response.length(), 0);
		}
	}
}
