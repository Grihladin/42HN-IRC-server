/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:51:58 by macbook           #+#    #+#             */
/*   Updated: 2025/10/02 16:45:00 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Definitions.hpp"
#include "../../inc/IrcServer.hpp"

int IrcServer::ircCommandPass(Command &command) {
  std::string response;
  std::string currentPassword = getPassword();
  if (command.getParams().empty()) {
    response = ERR_NEEDMOREPARAMS("*", "PASS");
    sendToFd(command.getUserFd(), response);
    return (0);
  }

  User *user = getUserByFd(command.getUserFd());
  std::string receivedPassword = command.getParams()[0].value;
  if (user && user->isRegistered()) {
    response = ERR_ALREADYREGISTRED("*");
    sendToFd(command.getUserFd(), response);
    return (0);
  }
  if (currentPassword == receivedPassword) {
    getUserByFd(command.getUserFd())->setAuthenticated();
    return (0);
  } else {
    response = ERR_PASSWDMISMATCH("*");
    sendToFd(command.getUserFd(), response);
    return (0);
  }
}
