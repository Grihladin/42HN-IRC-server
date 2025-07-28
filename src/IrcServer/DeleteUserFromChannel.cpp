/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteUserFromChannel.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 10:38:57 by psenko            #+#    #+#             */
/*   Updated: 2025/07/28 11:17:28 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/IrcServer.hpp"

int IrcServer::deleteUserFromAllChannels(int user_fd)
{
    for (Channel &iterCh : channels)
        iterCh.delUserFromChannel(user_fd);
    return (0);
}

int IrcServer::deleteUserFromChannel(std::string channelname, int user_fd)
{
    getChannelByName(channelname)->delUserFromChannel(user_fd);
    return (0);
}