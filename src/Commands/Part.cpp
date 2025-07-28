/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:51:36 by macbook           #+#    #+#             */
/*   Updated: 2025/07/28 18:52:17 by auplisas         ###   ########.fr       */
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
std::vector<std::string> split(const std::string &s, char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	for (char c : s)
	{
		if (c == delimiter)
		{
			if (!token.empty())
				tokens.push_back(token);
			token.clear();
		}
		else
		{
			token += c;
		}
	}
	if (!token.empty())
		tokens.push_back(token);
	return (tokens);
}

int IrcServer::ircCommandPart(Command &command)
{
	User	*user;
	Channel	*channel;

    int fd = command.getUserFd();
	user = getUserByFd(fd);
	if (!user || !user->isRegistered())
		return (sendToFd(command.getUserFd(), ERR_NOTREGISTERED("*")));
	const std::vector<paramstruct> &params = command.getParams();
	if (params.empty())
	{
		return (sendToFd(command.getUserFd(),
				ERR_NEEDMOREPARAMS(user->getNickName(), "PART")));
	}
	std::string partMessage = (params.size() > 1) ? params[1].value : "";
	std::vector<std::string> channelNames = split(params[0].value, ',');
	for (size_t i = 0; i < channelNames.size(); ++i)
	{
		std::string channelName = channelNames[i];
		if (!isChannelExist(channelName))
		{
			sendToFd(fd, ERR_NOSUCHCHANNEL(user->getNickName(), channelName));
			continue ;
		}
		channel = getChannelByName(channelName);
		if (!channel->isUserOnChannel(fd))
		{
			sendToFd(fd, ERR_NOTONCHANNEL(user->getNickName(), channelName));
			continue ;
		}
		channel->delUserFromChannel(fd);
		std::string prefix = ":" + user->getPrefix();
		std::string message = prefix + " PART " + channelName;
		if (!partMessage.empty())
			message += " :" + partMessage;
        message += "\r\n"; 
        auto& users = channel->getUsers();
        for (User* u : users)
        {
            sendToFd(u->getSocketFd(), message);
        }

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
	}
	return (0);
}
