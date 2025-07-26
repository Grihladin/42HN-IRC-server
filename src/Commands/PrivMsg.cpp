/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:52:30 by macbook           #+#    #+#             */
/*   Updated: 2025/07/26 19:07:40 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/Channel.hpp"
#include "../../Include/IrcServer.hpp"
#include "../../Include/User.hpp"

int IrcServer::ircCommandPrivMsg(Command &command) {
  User *user = getUserByFd(command.getUserFd());
  if (!user || !user->isRegistered()) {
    std::cerr << "Error: User not registered or does not exist." << std::endl;
    return (1);
  }

  const std::vector<paramstruct> &params = command.getParams();
  if (params.size() < 2) {
    sendToFd(user->getSocketFd(), ERR_NEEDMOREPARAMS(user->getNickName(), command.getCommand()));
    return (1);
  }

  std::string recipient = params[0].value;
  std::string message = params[1].value;
  std::string full_message = ":" + user->getNickName() + " PRIVMSG " +
                             recipient + " :" + message + "\r\n";

  if (recipient[0] == '#') {
    // It's a channel message
    Channel *channel = getChannelByName(recipient);
    if (!channel) {
      sendToFd(user->getSocketFd(), ERR_NOSUCHCHANNEL(user->getNickName(), recipient));
      return (1);
    }

    // Check if the user is on the channel
    if (!channel->isUserOnChannel(user->getSocketFd())) {
      sendToFd(user->getSocketFd(), ERR_CANNOTSENDTOCHAN(user->getNickName(), recipient));
      return (1);
    }

    const std::vector<User *> channel_users = channel->getUsers();
    for (size_t i = 0; i < channel_users.size(); ++i) {
      if (channel_users[i]->getSocketFd() != user->getSocketFd()) {
        sendToFd(channel_users[i]->getSocketFd(), full_message);
      }
    }
  } else {
    // It's a private message to a user
    User *target_user = getUserByNick(recipient);
    if (!target_user) {
      sendToFd(user->getSocketFd(), ERR_NOSUCHNICK(user->getNickName(), recipient));
      return (1);
    }

    sendToFd(target_user->getSocketFd(), full_message);
  }

  return (0);
}
