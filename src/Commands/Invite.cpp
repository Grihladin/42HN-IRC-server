/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:40:56 by psenko            #+#    #+#             */
/*   Updated: 2025/07/27 20:21:01 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/IrcServer.hpp"

int IrcServer::ircCommandInvite(Command& command)
{
	std::cout << "Executor: " << command.getCommand() << std::endl;

	if (command.paramCount() < 2)
	{
		sendToFd(command.getUserFd(), ERR_NEEDMOREPARAMS(getUserByFd(command.getUserFd())->getNickName(), "INVITE"));
		return 1;
	}

	std::string targetNick = command.getParams()[0].value;
	std::string channelName = command.getParams()[1].value;

	User* inviter = getUserByFd(command.getUserFd());
	User* targetUser = getUserByNick(targetNick);
	Channel* channel = getChannelByName(channelName);

	if (!channel)
	{
		sendToFd(inviter->getSocketFd(), ERR_NOSUCHCHANNEL(inviter->getNickName(), channelName));
		return 1;
	}

	if (!channel->isUser(inviter->getSocketFd()))
	{
		sendToFd(inviter->getSocketFd(), ERR_NOTONCHANNEL(inviter->getNickName(), channelName));
		return 1;
	}

	// Assume inviteOnly mode will be implemented later
	// If invite-only, require operator
	// if (channel->isInviteOnly() && !channel->isUserOperator(inviter->getSocketFd()))
	// {
	//     sendToFd(inviter->getSocketFd(), ERR_CHANOPRIVSNEEDED(inviter->getNickName(), channelName));
	//     return 1;
	// }

	if (!targetUser)
	{
		sendToFd(inviter->getSocketFd(), ERR_NOSUCHNICK(inviter->getNickName(), targetNick));
		return 1;
	}

	if (channel->isUser(targetUser->getSocketFd()))
	{
		sendToFd(inviter->getSocketFd(), ERR_USERONCHANNEL(inviter->getNickName(), targetNick, channelName));
		return 1;
	}

	// Success case: send RPL_INVITING and INVITE message
	sendToFd(inviter->getSocketFd(), RPL_INVITING(inviter->getNickName(), channelName, targetNick));

	std::string inviteMsg = ":" + inviter->getNickName() + "!" + inviter->getUserName() + "@localhost INVITE " + targetNick + " " + channelName + "\r\n";
	sendToFd(targetUser->getSocketFd(), inviteMsg);

	return 0;
}