/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:52:51 by macbook           #+#    #+#             */
/*   Updated: 2025/07/26 11:14:48 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/IrcServer.hpp"

int IrcServer::ircCommandQuit(Command& command)
{
    int user_fd = command.getUserFd();
    std::cout << "Executor: " << command.getCommand() << std::endl;
    deleteUser(user_fd);
    closeUserFd(user_fd);
    return (0);
}