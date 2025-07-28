/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:51:36 by macbook           #+#    #+#             */
/*   Updated: 2025/07/27 20:00:48 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/IrcServer.hpp"

// Parameters: <channel>{,<channel>}

// int IrcServer::ircCommandPart(Command& command)
// {
//     std::cout << "Executor: " << command.getCommand() << std::endl;
//     std::vector<struct paramstruct> params = command.getParams();
//     std::vector<struct paramstruct>::iterator iter;
//     for (iter = params.begin() ; iter != params.end() ; ++iter)
//     {
//         if ((*iter).name == std::string("channel"))
//         {
//             deleteUserFromChannel((*iter).value, command.getUserFd());
//         }
//     }
//     //NEED TO ADD ANSWERS
//     return (0);
// }

int IrcServer::ircCommandPart(Command &command)
{
	User	*user;
	Channel	*channel;

	user = getUserByFd(command.getUserFd());
	if (!user || !user->isRegistered())
		return (sendToFd(command.getUserFd(), ERR_NOTREGISTERED("*")));
	const std::vector<paramstruct> &params = command.getParams();
	if (params.empty())
    {
		return (sendToFd(command.getUserFd(), ERR_NEEDMOREPARAMS(user->getNickName(), "PART")));
    }
	std::string channelName;
	channelName = params[0].value;
	if (!isChannelExist(channelName))
	{
		sendToFd(command.getUserFd(), ERR_NOSUCHCHANNEL(user->getNickName(), channelName));
		return (1);
	}
	channel = getChannelByName(channelName);
	if (!channel || !channel->isUserOnChannel(command.getUserFd()))
	{
		sendToFd(command.getUserFd(), ERR_NOTONCHANNEL(user->getNickName(), channelName));
		return (1);
	}
	channel->delUserFromChannel(command.getUserFd());
	// If channel is empty delete it
	if (channel->getUsersCount() == 0)
	{
		std::vector<Channel>::iterator it = channels.begin();
		while (it != channels.end())
		{
			if (it->getName() == channelName)
			{
				it = channels.erase(it);
				break ;
			}
			else
				++it;
		}
	}
	return (0);
}
