/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:52:51 by macbook           #+#    #+#             */
/*   Updated: 2025/07/30 10:29:21 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/IrcServer.hpp"

int IrcServer::ircCommandQuit(Command& command)
{
    int user_fd = command.getUserFd();
    User* user = getUserByFd(user_fd);
    if (!user || !user->isRegistered())
	{
		sendToFd(user_fd, ERR_NOTREGISTERED());
		return (1);
	}

    std::string quitMessage = "Client Quit";
    if (command.paramCount() > 0)
    {
        const std::string &msg = command.getParams()[0].value;
        if (!msg.empty())
            quitMessage = msg;
    }

    std::string fullQuitMsg = RPL_QUIT(user->getPrefix(), quitMessage);

    // Broadcast to all users in all channels this user is part of
    for (std::vector<Channel>::iterator it = channels.begin(); it != channels.end(); ++it)
    {
        if (it->isUserOnChannel(user_fd))
        {
            const std::vector<User*> &channelUsers = it->getUsers();
            for (size_t i = 0; i < channelUsers.size(); ++i)
            {
                int other_fd = channelUsers[i]->getSocketFd();
                if (other_fd != user_fd)
                    sendToFd(other_fd, fullQuitMsg);
            }
        }
    }

    sendToFd(user_fd, RPL_ERROR_CLOSING_LINK(user->getPrefix(), quitMessage));
    deleteUserFromAllChannels(user_fd);
    deleteUser(user_fd);
    closeUserFd(user_fd);

    return 0;
}
