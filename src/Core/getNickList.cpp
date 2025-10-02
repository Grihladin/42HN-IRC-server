/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getNickList.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:35:30 by psenko            #+#    #+#             */
/*   Updated: 2025/10/02 16:45:00 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/IrcServer.hpp"

const std::vector<std::string> IrcServer::getNickList(std::string channelname) {
  Channel *curchannel = getChannelByName(channelname);
  return (curchannel->getNickList());
}

const std::string IrcServer::getNickListStr(std::string channelname) {
  Channel *curchannel = getChannelByName(channelname);
  return (curchannel->getNickListStr());
}
