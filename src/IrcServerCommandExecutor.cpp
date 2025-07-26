/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServerCommandExecutor.cpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:11:44 by psenko            #+#    #+#             */
/*   Updated: 2025/07/26 16:01:20 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/IrcServer.hpp"

void IrcServer::commandExecutor(Command &command)
{
	int 	nn = 0;
	std::cout << "Command entered is" << command.getCommand() << std::endl;

	for (nn = 0; nn < (COMMANDS_COUNT - 1); nn++)
	{
		if (irccommands[nn] == command.getCommand())
			break ;
	}
	(this->*executors[nn])(command);
}
