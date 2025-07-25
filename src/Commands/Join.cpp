/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:47:21 by macbook           #+#    #+#             */
/*   Updated: 2025/07/25 14:59:08 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/IrcServer.hpp"
#include "../../Include/Command.hpp"

//Parameters: <channel>{,<channel>} [<key>{,<key>}]

int IrcServer::ircCommandJoin(Command& command)
{
	int	client_fd = command.getUserFd();
	std::cout << "Executor: " << command.getCommand() << std::endl;
	std::vector<struct paramstruct> params = command.getParams();
	std::vector<struct paramstruct>::iterator iter;
	for (iter = params.begin() ; iter != params.end() ; ++iter)
	{
		if (iter->name == std::string("channel"))
			addUserToChannel(iter->value, client_fd);
	}
    return (0);
}
