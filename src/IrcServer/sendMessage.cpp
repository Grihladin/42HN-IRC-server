/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sendMessage.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 15:27:44 by psenko            #+#    #+#             */
/*   Updated: 2025/07/30 00:07:37 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/IrcServer.hpp"

int IrcServer::sendMessageToChannel(int user_fd, std::string channel,
                                    std::string &message) {
  Channel *channelObj = getChannelByName(channel);
  User *user = getUserByFd(user_fd);

  if (!user) {
    sendToFd(user_fd, ERR_NOTREGISTERED(user->getNickName()));
    return (1);
  }

  if (!channelObj) {
    sendToFd(user_fd, ERR_NOSUCHCHANNEL(user->getNickName(), channel));
    return (1);
  }

  // Check if the user is on the channel
  if (!channelObj->isUserOnChannel(user->getSocketFd())) {
    sendToFd(user_fd, ERR_CANNOTSENDTOCHAN(user->getNickName(), channel));
    return (1);
  }

  for (auto &channel_user : channelObj->getUsers()) {
    if (channel_user->getSocketFd() != user->getSocketFd()) {
      sendToFd(channel_user->getSocketFd(),
               RPL_CHANNEL_MESSAGE(user->getNickName(), channelObj->getName(),
                                   message));
    }
  }
  return (0);
}

int IrcServer::sendRawMessageToChannel(std::string channel, std::string reply) {
  Channel *channelObj = getChannelByName(channel);
  for (auto &channel_user : channelObj->getUsers())
    sendToFd(channel_user->getSocketFd(), reply);
  return (0);
}

int IrcServer::sendMessageToUser(int user_fd, std::string recipient,
                                 std::string &message) {
  User *user = getUserByFd(user_fd);
  User *target_user = getUserByNick(recipient);

  if (!target_user) {
    sendToFd(user_fd, ERR_NOSUCHNICK(user->getNickName(), recipient));
    return (1);
  }
  sendToFd(target_user->getSocketFd(),
           RPL_PRIV_MESSAGE(user->getNickName(), recipient, message));
  return (0);
}
