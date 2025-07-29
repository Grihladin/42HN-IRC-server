/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connectIsSuccesfull.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:56:02 by psenko            #+#    #+#             */
/*   Updated: 2025/07/29 11:16:52 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/IrcServer.hpp"

void IrcServer::connectIsSuccesfull(User *user)
{
    sendToFd(user->getSocketFd(), RPL_WELCOME(user->getNickName(), user->getUserName(), "server"));
    sendToFd(user->getSocketFd(), RPL_YOURHOST(user->getNickName(), "server", "v0.0.1"));
    sendToFd(user->getSocketFd(), RPL_CREATED(user->getNickName(), "Today"));
    // sendToFd(user->getSocketFd(), RPL_MYINFO(user->getNickName(), "server", "v0.0.1", "", "itkol"));
	sendToFd(user->getSocketFd(), RPL_MOTDSTART(user->getNickName(), "My supercool IRC server"));
	sendToFd(user->getSocketFd(), RPL_MOTD(user->getNickName(), "Hello! You are welcome!"));
	sendToFd(user->getSocketFd(), RPL_ENDOFMOTD(user->getNickName()));
}
