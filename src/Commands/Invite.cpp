/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:40:56 by psenko            #+#    #+#             */
/*   Updated: 2025/07/29 19:33:33 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/IrcServer.hpp"

int IrcServer::ircCommandInvite(Command& command)
{
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

	if (!inviter || !inviter->isRegistered())
	{
		sendToFd(inviter->getSocketFd(), ERR_NOTREGISTERED());
		return (1);
	}
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
	channel->addInvitedUser(targetUser);
	sendToFd(inviter->getSocketFd(), RPL_INVITING(inviter->getNickName(), channelName, targetNick));

	std::string inviteMsg = ":" + inviter->getNickName() + "!" + inviter->getUserName() + "@localhost INVITE " + targetNick + " " + channelName + "\r\n";
	sendToFd(targetUser->getSocketFd(), inviteMsg);

	return 0;
}