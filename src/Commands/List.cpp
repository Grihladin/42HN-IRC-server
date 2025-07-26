/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:48:47 by macbook           #+#    #+#             */
/*   Updated: 2025/07/26 12:24:37 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/IrcServer.hpp"

int IrcServer::ircCommandList(Command& command)
{
    //Command: getChannelList() with or without arguments
    std::vector<Channel>::iterator iter;
    std::cout << "Executor: " << command.getCommand() << std::endl;
    int user_fd = command.getUserFd();
    sendToFd(user_fd, RPL_LISTSTART());
    if (channels.size() > 0)
    {
        for (iter = channels.begin(); iter != channels.end(); ++iter)
        {
            std::string response = RPL_LIST(iter->getName(), iter->getUsersCount(), iter->getTopic());
            sendToFd(command.getUserFd(), response);
        }
    }
    sendToFd(user_fd, RPL_LISTEND());
    return (0);
}
