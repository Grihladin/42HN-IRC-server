/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:51:58 by macbook           #+#    #+#             */
/*   Updated: 2025/07/24 19:59:37 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/IrcServer.hpp"

// std::string IrcServer::ircCommandPass(const char *buffer, User *currentUser)
// {
// 	if (strncmp(buffer, "PASS ", 5) != 0 || currentUser->isAuthenticated())
// 		return "You need to authenticate first.\n";

// 	std::string receivedPassword(buffer + 5);

// 	receivedPassword.erase(receivedPassword.find_last_not_of(" \r\n") + 1);

// 	std::cout << "Expected password: [" << password << "]" << std::endl;
// 	std::cout << "Received password: [" << receivedPassword << "]" << std::endl;

// 	if (password == receivedPassword)
// 		return "Pass is correct.\n";
// 	else
// 		return "Wrong password.\n";
// }

int IrcServer::ircCommandPass(Command& command)
{
    //We get password of server
    //
    std::cout << "Executor: " << command.getCommand() << std::endl;
    addUser(command.getUserFd());
    getUserByFd(command.getUserFd())->setAuthenticated();
    //Reply has to be sent from here
    return (0);
}