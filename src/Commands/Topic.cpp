/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:53:16 by macbook           #+#    #+#             */
/*   Updated: 2025/07/27 18:46:15 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/IrcServer.hpp"
#include "../../Include/Definitions.hpp"

int IrcServer::ircCommandTopic(Command& command)
{
	int userFd = command.getUserFd();
	User* user = getUserByFd(userFd);

	if (!user || !user->isRegistered())
	{
		sendToFd(userFd, ERR_NOTREGISTERED());
		return 1;
	}

	const std::vector<paramstruct>& params = command.getParams();
	if (params.size() < 1)
	{
		sendToFd(userFd, ERR_NEEDMOREPARAMS(user->getNickName(), "TOPIC"));
		return 1;
	}

	std::string channelName = params[0].value;
	Channel* channel = getChannelByName(channelName);
	if (!channel)
	{
		sendToFd(userFd, ERR_NOSUCHCHANNEL(user->getNickName(), channelName));
		return 1;
	}

	if (!channel->isUserOnChannel(userFd))
	{
		sendToFd(userFd, ERR_NOTONCHANNEL(user->getNickName(), channelName));
		return 1;
	}

	if (params.size() == 1)
	{
		std::string topic = channel->getTopic();
		if (topic.empty())
			sendToFd(userFd, RPL_NOTOPIC(user->getNickName(), channelName));
		else
			sendToFd(userFd, RPL_TOPIC(user->getNickName(), channelName, topic));
		return 0;
	}

	// if (!channel->isUserOperator(userFd))
	// {
	// 	sendToFd(userFd, ERR_CHANOPRIVSNEEDED(user->getNickName(), channelName));
	// 	return 1;
	// }

	std::string newTopic = params[1].value;
	channel->setTopic(newTopic, userFd);

	std::string response = ":" + user->getNickName() + " TOPIC " + channelName + " :" + channel->getTopic() + "\r\n";
	const std::vector<std::string> nicklist = getNickList(channelName);
	for (const std::string& nick : nicklist)
	{
        (void)nick;
		User* recipient = getUserByFd(userFd);
		if (recipient)
			sendToFd(recipient->getSocketFd(), response);
	}
	return 0;
}