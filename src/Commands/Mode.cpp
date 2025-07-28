/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:49:21 by macbook           #+#    #+#             */
/*   Updated: 2025/07/28 11:32:06 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/IrcServer.hpp"

int IrcServer::ircCommandMode(Command& command)
{
    std::cout << "Executor: " << command.getCommand() << std::endl;
    User *user = getUserByFd(command.getUserFd());
    if (!user || !user->isRegistered())
    {
        std::cerr << "Error: User not registered or does not exist." << std::endl;
        return (1);
    }
    const std::vector<paramstruct> &params = command.getParams();
    if (params.size() < 2) {
        sendToFd(user->getSocketFd(), ERR_NEEDMOREPARAMS(user->getNickName(), command.getCommand()));
        return (1);
    }
    std::string recipient = params[0].value;
    std::string message = params[1].value;

    if (recipient[0] == '#')
    {
        //MODE for channel
        ;
    }
    else
    {
        //MODE for user
        ;
    }
    return (0);
}