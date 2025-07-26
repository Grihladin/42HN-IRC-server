/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:47:21 by macbook           #+#    #+#             */
/*   Updated: 2025/07/26 11:28:50 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/IrcServer.hpp"

//Parameters: <channel>{,<channel>} [<key>{,<key>}]

int IrcServer::ircCommandJoin(Command& command)
{
	int	client_fd = command.getUserFd();
	std::cout << "Executor: " << command.getCommand() << std::endl;
	std::vector<struct paramstruct> params = command.getParams();
	std::vector<struct paramstruct>::iterator iter;
	Channel	*tmpChannel;
	for (iter = params.begin() ; iter != params.end() ; ++iter)
	{
		if (iter->name == std::string("middle"))
		{
			tmpChannel = addUserToChannel(iter->value, client_fd);
			if (tmpChannel)
			{
				std::string topic = tmpChannel->getTopic();
				std::string response;
				if (topic.length() > 0)
					response = RPL_TOPIC(iter->value, topic);
				else
					response = RPL_NOTOPIC(iter->value);
				send(client_fd, response.c_str(), response.length(), 0);
			}
		}
	}
    return (0);
}
