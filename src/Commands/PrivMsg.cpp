/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:52:30 by macbook           #+#    #+#             */
/*   Updated: 2025/07/26 15:55:26 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/IrcServer.hpp"

int IrcServer::ircCommandPrivMsg(Command& command)
{
    //Check if message is sent to user or channel
    //Check that recipent exists
    //send message using sendmessagetousercommand
    int user_fd = command.getUserFd();
    std::cout << "Executor: " << command.getCommand() << std::endl;
    std::vector<struct paramstruct> params = command.getParams();
    std::string target = params[0].value;
    std::string msg = params[1].value;
    if ((target[0] != '#') && (target[0] != '&'))
    {
        sendMessageToUser(user_fd, target, msg);
    }
    else
    {
        sendMessageToChannel(user_fd, target, msg);
    }
    return (0);
}