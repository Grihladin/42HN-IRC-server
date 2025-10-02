/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:53:34 by macbook           #+#    #+#             */
/*   Updated: 2025/10/02 16:45:00 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Definitions.hpp"
#include "../../inc/IrcServer.hpp"

int IrcServer::ircCommandUser(Command &command) {
  int userFd;
  User *user;

  userFd = command.getUserFd();
  user = getUserByFd(userFd);
  if (!user || !user->isAuthenticated()) {
    std::string response = ERR_PASSWDMISMATCH("*");
    sendToFd(userFd, response);
    return (1);
  }
  if (user->isRegistered()) {
    std::string response = ERR_ALREADYREGISTRED();
    sendToFd(userFd, response);
    return (1);
  }
  const std::vector<paramstruct> &params = command.getParams();
  if (params.size() < 4) {
    std::string response = ERR_NEEDMOREPARAMS("*", "USER");
    sendToFd(userFd, response);
    return (1);
  }
  user->setUsername(params[0].value);
  user->setRealname(params[3].value);
  if (!user->getNickName().empty()) {
    user->setRegistered();
    connectIsSuccesfull(getUserByFd(userFd));
  }
  return (0);
}
