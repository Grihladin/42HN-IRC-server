/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:52:30 by macbook           #+#    #+#             */
/*   Updated: 2025/10/02 16:45:00 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Channel.hpp"
#include "../../inc/IrcServer.hpp"
#include "../../inc/User.hpp"

int IrcServer::ircCommandPrivMsg(Command &command) {
  User *user = getUserByFd(command.getUserFd());

  if (!user || !user->isRegistered()) {
    sendToFd(command.getUserFd(), ERR_NOTREGISTERED());
    return (1);
  }

  const std::vector<paramstruct> &params = command.getParams();
  if (params.size() < 2) {
    sendToFd(user->getSocketFd(),
             ERR_NEEDMOREPARAMS(user->getNickName(), command.getCommand()));
    return (1);
  }

  std::vector<std::string> recipients = split(params[0].value, ',');
  std::string message = params[1].value;

  if (message.empty()) {
    sendToFd(user->getSocketFd(), ERR_NOTEXTTOSEND(user->getNickName()));
    return (1);
  }

  bool notice = false;
  if (command.getCommand() == "NOTICE")
    notice = true;

  for (auto &recipient : recipients) {
    if (recipient[0] == '#') {
      // It's a channel message
      if (sendMessageToChannel(user->getSocketFd(), recipient, message,
                               notice) != 0) {
        std::cerr << "Error: Failed to send message to channel." << std::endl;
        return (1);
      }
    } else {
      // It's a private message to a user
      if (sendMessageToUser(user->getSocketFd(), recipient, message, notice) !=
          0) {
        std::cerr << "Error: Failed to send private message." << std::endl;
        return (1);
      }
    }
  }
  return (0);
}
