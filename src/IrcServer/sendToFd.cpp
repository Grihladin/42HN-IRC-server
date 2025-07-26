/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sendToFd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 11:38:46 by psenko            #+#    #+#             */
/*   Updated: 2025/07/26 12:32:30 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/IrcServer.hpp"

int IrcServer::sendToFd(int user_fd, std::string message)
{
    std::cout << "Send to fd " << user_fd << " message: " << message << std::endl;
    send(user_fd, message.c_str(), message.length(), 0);
    return (0);
}