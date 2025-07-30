/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wrong.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 10:30:43 by psenko            #+#    #+#             */
/*   Updated: 2025/07/30 10:24:10 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/IrcServer.hpp"

int IrcServer::ircCommandWrong(Command& command)
{
	int		fd = command.getUserFd();
    User	*user = getUserByFd(fd);
    
    if (fd >= 0)
    {
        std::string nick = "*";
        if (user)
        {
            nick = user->getNickName();
            if (nick.empty())
                nick = "*";
        }
        std::string cmd = command.getCommand();
        std::string response = ERR_UNKNOWNCOMMAND("*", cmd);
        sendToFd(fd, response);
    }
    return (0);
}