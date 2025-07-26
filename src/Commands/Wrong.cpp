/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wrong.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 10:30:43 by psenko            #+#    #+#             */
/*   Updated: 2025/07/26 14:34:47 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/IrcServer.hpp"

int IrcServer::ircCommandWrong(Command& command)
{
    User	*user;
	int		fd;

    fd = command.getUserFd();
    if (fd >= 0)
    {
        user = getUserByFd(fd);
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