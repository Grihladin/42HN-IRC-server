/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:52:51 by macbook           #+#    #+#             */
/*   Updated: 2025/07/29 16:53:00 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/IrcServer.hpp"

int IrcServer::ircCommandQuit(Command &command) {
  std::vector<paramstruct> params = command.getParams();
  int user_fd = command.getUserFd();
  std::string quitMessage = "Client Quit"; // Default message

  for (auto &param : params) {
    if (param.name == "trailing" && !param.value.empty()) {
      quitMessage = param.value;
      break;
    }
  }
  sendToFd(user_fd, RPL_QUIT(getUserByFd(user_fd)->getNickName(), quitMessage));
  deleteUserFromAllChannels(user_fd);
  deleteUser(user_fd);
  closeUserFd(user_fd);
  return 0;
}
