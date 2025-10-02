/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:53:16 by macbook           #+#    #+#             */
/*   Updated: 2025/10/02 16:45:00 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Definitions.hpp"
#include "../../inc/IrcServer.hpp"

int IrcServer::ircCommandTopic(Command &command) {
  int userFd = command.getUserFd();
  User *user = getUserByFd(userFd);

  if (!user || !user->isRegistered()) {
    sendToFd(userFd, ERR_NOTREGISTERED());
    return (1);
  }

  const std::vector<paramstruct> &params = command.getParams();
  if (params.size() < 1) {
    sendToFd(userFd, ERR_NEEDMOREPARAMS(user->getNickName(), "TOPIC"));
    return (1);
  }

  std::string channelName = params[0].value;
  Channel *channel = getChannelByName(channelName);
  if (!channel) {
    sendToFd(userFd, ERR_NOSUCHCHANNEL(user->getNickName(), channelName));
    return (1);
  }

  if (!channel->isUserOnChannel(userFd)) {
    sendToFd(userFd, ERR_NOTONCHANNEL(user->getNickName(), channelName));
    return (1);
  }

  if (params.size() == 1) {
    std::string topic = channel->getTopic();
    if (topic.empty())
      sendToFd(userFd, RPL_NOTOPIC(user->getNickName(), channelName));
    else
      sendToFd(userFd, RPL_TOPIC(user->getNickName(), channelName, topic));
    return (0);
  }

  if (channel->isRestrictTopic() && !channel->isUserOperator(userFd)) {
    sendToFd(userFd, ERR_CHANOPRIVSNEEDED(user->getNickName(), channelName));
    return (1);
  }

  std::string newTopic =
      (params.size() > 1 && !params[1].value.empty()) ? params[1].value : "";
  channel->setTopic(newTopic, userFd);

  std::string response =
      RPL_TOPIC(user->getNickName(), channelName, channel->getTopic());
  const std::vector<std::string> nicklist = getNickList(channelName);
  for (const std::string &nick : nicklist) {
    User *recipient = getUserByNick(nick);
    if (recipient)
      sendToFd(recipient->getSocketFd(), response);
  }
  return (0);
}
