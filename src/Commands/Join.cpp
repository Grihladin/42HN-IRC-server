/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:47:21 by macbook           #+#    #+#             */
/*   Updated: 2025/07/28 22:03:33 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/IrcServer.hpp"

// Parameters: <channel>{,<channel>} [<key>{,<key>}]

int IrcServer::ircCommandJoin(Command &command) {
  int client_fd = command.getUserFd();
  User *user = getUserByFd(client_fd);

  for (auto &iter : command.getParams()) {
    if (iter.name == std::string("last")) {
      Channel *channel = getChannelByName(iter.value);
      if (channel && channel->isUserOnChannel(client_fd))
        continue;
      if (channel && channel->isInviteOnly()) {
          if (!channel->isUserInvited(user)) {
              sendToFd(client_fd, ERR_INVITEONLYCHAN(user->getNickName(), iter.value));
              continue;
          }
          else
          {
            channel->removeInvitedUser(user);
          }
      }
      channel = addUserToChannel(iter.value, client_fd);
      if (channel) {
        // Get the channel's topic
        std::string topic = channel->getTopic();
        std::string response;

        // Send the topic to the user who just joined
        if (topic.length() > 0) {
          response = RPL_TOPIC(user->getNickName(), iter.value, topic);
        } else {
          response = RPL_NOTOPIC(user->getNickName(), iter.value);
        }
        sendToFd(client_fd, response);

        // Get the list of nicks in the channel and send it to the user
        std::string user_list = getNickListStr(iter.value);
        response =
            RPL_NAMREPLY(user->getNickName(), "=", iter.value, user_list);
        sendToFd(client_fd, response);
        response = RPL_ENDOFNAMES(user->getNickName(), iter.value);
        sendToFd(client_fd, response);

        // Notify all users in the channel that a new user has joined
        response = "JOIN " + iter.value;
        if (sendMessageToChannel(client_fd, iter.value, response) != 0) {
          std::cerr << "Error: Failed to send JOIN message to channel "
                    << iter.value << std::endl;
          return (1);
        }
      }
    }
  }
  return (0);
}
