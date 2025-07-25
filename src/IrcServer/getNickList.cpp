/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getNickList.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:35:30 by psenko            #+#    #+#             */
/*   Updated: 2025/07/25 16:04:15 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/IrcServer.hpp"

const std::vector<std::string> IrcServer::getNickList(std::string channelname)
{
    Channel* curchannel = getChannelByName(channelname);
    return (curchannel->getNickList());
}

const std::string IrcServer::getNickListStr(std::string channelname)
{
    Channel* curchannel = getChannelByName(channelname);
    return (curchannel->getNickListStr());
}
