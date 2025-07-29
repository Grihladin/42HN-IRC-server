/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:08:41 by mratke            #+#    #+#             */
/*   Updated: 2025/07/29 17:47:34 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/Channel.hpp"
#include "../../Include/Command.hpp"
#include "../../Include/Definitions.hpp"
#include "../../Include/IrcServer.hpp"
#include "../../Include/User.hpp"

int IrcServer::ircCommandWho(Command &command) {
  int userFd = command.getUserFd();
  User *user = getUserByFd(userFd);

  if (!user || !user->isAuthenticated()) {
    sendToFd(userFd, ERR_NOTREGISTERED(user->getNickName()));
    return 1;
  }

  std::string mask = "*";
  if (command.paramCount() > 0)
    mask = command.getParams()[0].value;

  sendToFd(userFd, RPL_WHOREPLY(user->getNickName(), ""));
  sendToFd(userFd, RPL_ENDOFWHO(user->getNickName(), mask));
  return 0;
}
