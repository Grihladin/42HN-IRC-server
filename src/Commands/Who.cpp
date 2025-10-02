/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:08:41 by mratke            #+#    #+#             */
/*   Updated: 2025/10/02 16:45:00 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Channel.hpp"
#include "../../inc/Command.hpp"
#include "../../inc/Definitions.hpp"
#include "../../inc/IrcServer.hpp"
#include "../../inc/User.hpp"

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
  Channel *channel = getChannelByName(mask);

  if (mask[0] == '#') {
    // If mask is #, we assume it's a channel and send list of users.
    if (!channel) {
      sendToFd(userFd, ERR_NOSUCHCHANNEL(user->getNickName(), mask));
      return 1;
    }
    for (auto &channel_user : channel->getUsers()) {
      sendToFd(userFd, RPL_WHOREPLY(user->getNickName(), channel->getName(),
                                    channel_user->getUserName(),
                                    channel_user->getHostName(), "server",
                                    channel_user->getNickName(), "H", "0",
                                    channel_user->getRealName()));
    }
  } else {
    // If mask is not a channel, we assume it's a user nickname
    User *targetUser = getUserByNick(mask);
    if (!targetUser) {
      sendToFd(userFd, ERR_NOSUCHNICK(user->getNickName(), mask));
      return 1;
    }
    sendToFd(userFd,
             RPL_WHOREPLY(user->getNickName(), "*", targetUser->getUserName(),
                          targetUser->getHostName(), "server",
                          targetUser->getNickName(), "H", "0",
                          targetUser->getRealName()));
  }
  sendToFd(userFd, RPL_ENDOFWHO(user->getNickName(), mask));
  return 0;
}
// Add @ if user is operator
// Add User modes when modes ready
