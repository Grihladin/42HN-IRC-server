/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteUserFromChannel.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 10:38:57 by psenko            #+#    #+#             */
/*   Updated: 2025/07/26 10:44:39 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/IrcServer.hpp"

int IrcServer::deleteUserFromAllChannels(int user_fd)
{
    std::vector<Channel>::iterator iterCh;
    for (iterCh = channels.begin() ; iterCh != channels.end() ; ++iterCh)
    {
        (*iterCh).delUserFromChannel(user_fd);
    }
    return (0);
}

int IrcServer::deleteUserFromChannel(std::string channelname, int user_fd)
{
    std::vector<Channel>::iterator iterCh;
    for (iterCh = channels.begin() ; iterCh != channels.end() ; ++iterCh)
    {
        if ((*iterCh).getName() == channelname)
        {
            (*iterCh).delUserFromChannel(user_fd);
            break;
        }
    }
    return (0);
}