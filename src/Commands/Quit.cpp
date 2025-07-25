/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:52:51 by macbook           #+#    #+#             */
/*   Updated: 2025/07/25 10:24:16 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/IrcServer.hpp"

int IrcServer::ircCommandQuit(Command& command)
{
    
    std::cout << "Executor: " << command.getCommand() << std::endl;
    deleteUser(command.getUserFd());
    return (0);
}