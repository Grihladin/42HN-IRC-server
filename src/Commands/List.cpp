/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:48:47 by macbook           #+#    #+#             */
/*   Updated: 2025/07/29 19:44:51 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/IrcServer.hpp"

int IrcServer::ircCommandList(Command& command)
{
    std::vector<Channel>::iterator iter;
    int user_fd = command.getUserFd();
    User *user = getUserByFd(command.getUserFd());
    if (!user || !user->isRegistered())
	{
		sendToFd(user_fd, ERR_NOTREGISTERED());
		return (1);
	}
    if (channels.size() > 0)
    {
        for (iter = channels.begin(); iter != channels.end(); ++iter)
        {
            std::string response = RPL_LIST("*", iter->getName(), iter->getUsersCount(), iter->getTopic());
            sendToFd(command.getUserFd(), response);
        }
    }
    sendToFd(user_fd, RPL_LISTEND("*"));
    return (0);
}
