/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getChannel.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:56:08 by psenko            #+#    #+#             */
/*   Updated: 2025/10/02 16:45:00 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/IrcServer.hpp"

Channel *IrcServer::getChannelByName(std::string channelname) {
  for (std::vector<Channel>::iterator iter = channels.begin();
       iter != channels.end(); ++iter) {
    if (iter->getName() == channelname)
      return (&(*iter));
  }
  return (nullptr);
}
