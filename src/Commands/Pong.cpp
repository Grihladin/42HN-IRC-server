/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pong.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 13:42:55 by mratke            #+#    #+#             */
/*   Updated: 2025/07/26 14:16:26 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/IrcServer.hpp"

int IrcServer::ircCommandPong(Command& command)
{
    (void)command;
    // The PONG command is a reply to a PING command. 
	// When the server receives a PONG command from a client, the only action is to not disconnect the client.
    // So we do nothing here.
    return (0);
}
