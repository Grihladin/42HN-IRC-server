/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:47:21 by macbook           #+#    #+#             */
/*   Updated: 2025/10/02 16:45:00 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/IrcServer.hpp"

// Parameters: <channel>{,<channel>} [<key>{,<key>}]

int IrcServer::ircCommandJoin(Command &command) {
  int client_fd = command.getUserFd();
  User *user = getUserByFd(client_fd);
  std::vector<std::string> channels;
  std::vector<std::string> keys;
  std::string channel_str, key_str;

  if (!user || !user->isRegistered()) {
    sendToFd(client_fd, ERR_NOTREGISTERED());
    return (1);
  }
  if (command.paramCount() < 1) {
    sendToFd(client_fd,
             ERR_NEEDMOREPARAMS(user->getNickName(), command.getCommand()));
    return (1);
  }
  for (auto &iter : command.getParams()) {
    if (iter.name == "middle") {
      channel_str = iter.value;
    } else if (iter.name == "last") {
      if (channel_str.empty()) {
        channel_str = iter.value;
      } else {
        key_str = iter.value;
      }
    }
  }

  channels = split(channel_str, ',');
  if (!key_str.empty()) {
    keys = split(key_str, ',');
  }

  for (size_t i = 0; i < channels.size(); ++i) {
    std::string channel_name = channels[i];
    if (channel_name.empty() || channel_name[0] != '#') {
      sendToFd(client_fd, ERR_BADCHANMASK(user->getNickName(), channel_name));
      continue;
    }
    std::string key = (i < keys.size()) ? keys[i] : "";

    Channel *channel = getChannelByName(channel_name);
    if (channel && channel->isUserOnChannel(client_fd)) {
      sendToFd(client_fd, ERR_USERONCHANNEL(user->getNickName(),
                                            user->getUserName(), channel_name));
      continue;
    }

    if (channel && channel->isKey() && (channel->getKey() != key)) {
      sendToFd(client_fd, ERR_BADCHANNELKEY(user->getNickName(), channel_name));
      continue;
    }
    if (channel) {
      std::cout << "User limit: " << channel->getUserLimit() << std::endl;
      std::cout << "User count: " << channel->getUsersCount() << std::endl;
    }
    if (channel && (channel->getUserLimit() > 0) &&
        (channel->getUsersCount() >= (channel->getUserLimit()))) {
      sendToFd(client_fd, ERR_CHANNELISFULL(user->getNickName(), channel_name));
      continue;
    }
    if (channel && channel->isInviteOnly()) {
      if (!channel->isUserInvited(user)) {
        sendToFd(client_fd,
                 ERR_INVITEONLYCHAN(user->getNickName(), channel_name));
        continue;
      } else {
        channel->removeInvitedUser(user);
      }
    }
    channel = addUserToChannel(channel_name, client_fd);

    if (channel) {
      // Get the channel's topic
      std::string topic = channel->getTopic();
      std::string response;
      std::string user_nick = user->getNickName();

      // Send the topic to the user who just joined
      if (topic.length() > 0) {
        sendToFd(client_fd, RPL_TOPIC(user_nick, channel_name, topic));
      } else {
        sendToFd(client_fd, RPL_NOTOPIC(user_nick, channel_name));
      }

      // Notify all users in the channel that a new user has joined
      sendRawMessageToChannel(channel_name,
                              RPL_JOIN(user_nick, user->getUserName(),
                                       user->getHostName(), channel_name));

      // Get the list of nicks in the channel and send it to the user
      sendToFd(client_fd, RPL_NAMREPLY(user_nick, "=", channel_name,
                                       getNickListStr(channel_name)));
      sendToFd(client_fd, RPL_ENDOFNAMES(user_nick, channel_name));
    }
  }
  return (0);
}
