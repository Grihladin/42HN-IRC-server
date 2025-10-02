/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteUserFromChannel.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 10:38:57 by psenko            #+#    #+#             */
/*   Updated: 2025/10/02 16:45:00 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/IrcServer.hpp"

int IrcServer::deleteUserFromAllChannels(int user_fd) {
  for (Channel &iterCh : channels)
    iterCh.delUserFromChannel(user_fd);
  return (0);
}

int IrcServer::deleteUserFromChannel(std::string channelname, int user_fd) {
  getChannelByName(channelname)->delUserFromChannel(user_fd);
  return (0);
}
