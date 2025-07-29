/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:47:21 by macbook           #+#    #+#             */
/*   Updated: 2025/07/29 15:52:09 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/IrcServer.hpp"

// Parameters: <channel>{,<channel>} [<key>{,<key>}]

int IrcServer::ircCommandJoin(Command &command) {
  int client_fd = command.getUserFd();
  User *user = getUserByFd(client_fd);
  std::vector<std::string> channels;
  std::vector<std::string> keys;
  std::string channel_str, key_str;

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
    std::string key = (i < keys.size()) ? keys[i] : "";

    Channel *channel = getChannelByName(channel_name);
    if (channel && channel->isUserOnChannel(client_fd))
      continue;

    if (channel && channel->isKey() && channel->getKey() != key) {
      sendToFd(client_fd, ERR_BADCHANNELKEY(user->getNickName(), channel_name));
      continue;
    }

    channel = addUserToChannel(channel_name, client_fd);
    if (channel) {
      // Get the channel's topic
      std::string topic = channel->getTopic();
      std::string response;

      // Send the topic to the user who just joined
      if (topic.length() > 0) {
        response = RPL_TOPIC(user->getNickName(), channel_name, topic);
      } else {
        response = RPL_NOTOPIC(user->getNickName(), channel_name);
      }
      sendToFd(client_fd, response);

      // Get the list of nicks in the channel and send it to the user
      std::string user_list = getNickListStr(channel_name);
      response =
          RPL_NAMREPLY(user->getNickName(), "=", channel_name, user_list);
      sendToFd(client_fd, response);
      response = RPL_ENDOFNAMES(user->getNickName(), channel_name);
      sendToFd(client_fd, response);

      // Notify all users in the channel that a new user has joined
      response = RPL_JOIN(user->getNickName(), "", "server", channel_name);
      // sendToFd(client_fd, response);
      // if (sendMessageToChannel(client_fd, channel_name, response) != 0) {
      sendRawMessageToChannel(channel_name, response);
      //   std::cerr << "Error: Failed to send JOIN message to channel "
      //             << channel_name << std::endl;
      //   return (1);
      // }
    }
  }
  return (0);
}
