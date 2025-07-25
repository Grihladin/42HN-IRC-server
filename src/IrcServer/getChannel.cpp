/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getChannel.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:56:08 by psenko            #+#    #+#             */
/*   Updated: 2025/07/25 15:58:35 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/IrcServer.hpp"

Channel* IrcServer::getChannelByName(std::string channelname)
{
    for (std::vector<Channel>::iterator iter = channels.begin() ; iter != channels.end() ; ++iter)
    {
        if (iter->getName() == channelname)
            return (&(*iter));
    }
    return (nullptr);
}
