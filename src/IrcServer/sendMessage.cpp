/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sendMessage.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 15:27:44 by psenko            #+#    #+#             */
/*   Updated: 2025/07/26 16:02:27 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/IrcServer.hpp"

int IrcServer::sendMessageToChannel(int user_fd, std::string channel, std::string &message)
{
    std::string response = RPL_CHANNEL_MESSAGE("*", channel, message);
    std::cout << "Message from " << user_fd << ": " << response;
    // sendToFd(user_fd, response);
    return (0);
}

int IrcServer::sendMessageToUser(int user_fd, std::string user, std::string &message)
{
    std::string response = RPL_PRIV_MESSAGE("*", message);
    std::cout << "Message from " << user_fd << " " << user << ": " << response;
    // sendToFd(user_fd, response);
    return (0);
}
