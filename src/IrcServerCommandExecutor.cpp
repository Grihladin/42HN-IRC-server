/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServerCommandExecutor.cpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:11:44 by psenko            #+#    #+#             */
/*   Updated: 2025/07/25 00:26:52 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/IrcServer.hpp"

void IrcServer::commandExecutor(Command &command)
{
	bool matched = false;
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
		int fd = command.getUserFd();
		if (fd >= 0)
		{
			std::string response = "Invalid Command Entered\n";
			send(fd, response.c_str(), response.length(), 0);
		}
	}
}
