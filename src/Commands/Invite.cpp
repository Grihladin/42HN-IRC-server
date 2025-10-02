/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:40:56 by psenko            #+#    #+#             */
/*   Updated: 2025/10/02 16:45:00 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/IrcServer.hpp"

int IrcServer::ircCommandInvite(Command &command) {
  int user_fd = command.getUserFd();
  User *user = getUserByFd(user_fd);
  if (!user || !user->isRegistered()) {
    sendToFd(user_fd, ERR_NOTREGISTERED());
    return (1);
  }
  if (command.paramCount() < 2) {
    sendToFd(command.getUserFd(),
             ERR_NEEDMOREPARAMS(getUserByFd(command.getUserFd())->getNickName(),
                                "INVITE"));
    return 1;
  }

  std::string targetNick = command.getParams()[0].value;
  std::string channelName = command.getParams()[1].value;

  User *targetUser = getUserByNick(targetNick);
  Channel *channel = getChannelByName(channelName);
  User *inviter = getUserByFd(command.getUserFd());

  if (!channel) {
    sendToFd(inviter->getSocketFd(),
             ERR_NOSUCHCHANNEL(inviter->getNickName(), channelName));
    return 1;
  }

  if (!channel->isUser(inviter->getSocketFd())) {
    sendToFd(inviter->getSocketFd(),
             ERR_NOTONCHANNEL(inviter->getNickName(), channelName));
    return 1;
  }

  if (!targetUser) {
    sendToFd(inviter->getSocketFd(),
             ERR_NOSUCHNICK(inviter->getNickName(), targetNick));
    return 1;
  }

  if (channel->isUser(targetUser->getSocketFd())) {
    sendToFd(
        inviter->getSocketFd(),
        ERR_USERONCHANNEL(inviter->getNickName(), targetNick, channelName));
    return 1;
  }
  if (channel->isInviteOnly() && !channel->isUserOperator(user_fd)) {
    sendToFd(user_fd, ERR_CHANOPRIVSNEEDED(user->getNickName(), channelName));
    return (1);
  }
  channel->addInvitedUser(targetUser);
  sendToFd(inviter->getSocketFd(),
           RPL_INVITING(inviter->getNickName(), channelName, targetNick));

  std::string inviteMsg = ":" + inviter->getNickName() + "!" +
                          inviter->getUserName() + "@localhost INVITE " +
                          targetNick + " " + channelName + "\r\n";
  sendToFd(targetUser->getSocketFd(), inviteMsg);

  return 0;
}
