/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wrong.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 10:30:43 by psenko            #+#    #+#             */
/*   Updated: 2025/07/26 11:32:42 by psenko           ###   ########.fr       */
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
        std::string response = ERR_UNKNOWNCOMMAND(cmd);
        send(fd, response.c_str(), response.length(), 0);
    }
    return (0);
}