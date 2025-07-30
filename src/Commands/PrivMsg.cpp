/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:52:30 by macbook           #+#    #+#             */
/*   Updated: 2025/07/30 10:28:23 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/Channel.hpp"
#include "../../Include/IrcServer.hpp"
#include "../../Include/User.hpp"

int IrcServer::ircCommandPrivMsg(Command &command) {
  User *user = getUserByFd(command.getUserFd());

  if (!user || !user->isRegistered()) {
    sendToFd(client_fd, ERR_NOTREGISTERED());
    return (1);
  }

  const std::vector<paramstruct> &params = command.getParams();
  if (params.size() < 2) {
    sendToFd(user->getSocketFd(),
             ERR_NEEDMOREPARAMS(user->getNickName(), command.getCommand()));
    return (1);
  }

  std::string recipient = params[0].value;
  std::string message = params[1].value;

  if (recipient[0] == '#') {
    // It's a channel message
    if (sendMessageToChannel(user->getSocketFd(), recipient, message) != 0) {
      std::cerr << "Error: Failed to send message to channel." << std::endl;
      return (1);
    }
  } else {
    // It's a private message to a user
    if (sendMessageToUser(user->getSocketFd(), recipient, message) != 0) {
      std::cerr << "Error: Failed to send private message." << std::endl;
      return (1);
    }
  }
  return (0);
}
