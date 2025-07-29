/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:48:19 by macbook           #+#    #+#             */
/*   Updated: 2025/07/28 20:39:26 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/IrcServer.hpp"

int IrcServer::ircCommandKick(Command& command)
{
    std::cout << "Executor: " << command.getCommand() << std::endl;

    User* kicker = getUserByFd(command.getUserFd());
    std::string yournick = kicker->getNickName();

    if (command.paramCount() < 2) {
        sendToFd(command.getUserFd(), ERR_NEEDMOREPARAMS(yournick, command.getCommand()));
        return (1);
    }

    std::string channelName = command.getParams()[0].value;
    std::string targetNick = command.getParams()[1].value;
    std::string comment = "";

    if (command.paramCount() >= 3) {
        comment = command.getParams()[2].value;
    } else {
        comment = "Kicked by " + yournick;
    }

    Channel* channel = getChannelByName(channelName);
    if (!channel) {
        sendToFd(command.getUserFd(), ERR_NOSUCHCHANNEL(yournick, channelName));
        return (1);
    }

    if (!channel->isUserOnChannel(kicker->getSocketFd())) {
        sendToFd(command.getUserFd(), ERR_NOTONCHANNEL(yournick, channelName));
        return (1);
    }

    if (!channel->isUserOperator(kicker->getSocketFd())) {
        sendToFd(command.getUserFd(), ERR_CHANOPRIVSNEEDED(yournick, channelName));
        return (1);
    }
    
    User* targetUser = getUserByNick(targetNick);
    if (!targetUser) {
        sendToFd(command.getUserFd(), ERR_NOSUCHNICK(yournick, targetNick));
        return (1);
    }

    if (!channel->isUserOnChannel(targetUser->getSocketFd())) {
        sendToFd(command.getUserFd(), ERR_USERNOTINCHANNEL(yournick, targetNick, channelName));
        return (1);
    }

    std::string kickMessage = ":" + kicker->getNickName() + "!" + kicker->getUserName() + "@server KICK " + channelName + " " + targetNick + " :" + comment + "\r\n";
    const std::vector<User*>& usersInChannel = channel->getUsers();
    for (size_t i = 0; i < usersInChannel.size(); ++i) {
        sendToFd(usersInChannel[i]->getSocketFd(), kickMessage);
    }
    
    channel->delUserFromChannel(targetUser->getSocketFd());
    
    if (channel->getUsersCount() == 0) {
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