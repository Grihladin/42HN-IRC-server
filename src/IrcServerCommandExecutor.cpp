/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServerCommandExecutor.cpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:11:44 by psenko            #+#    #+#             */
/*   Updated: 2025/07/24 11:44:13 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/IrcServer.hpp"

void IrcServer::commandExecutor(Command& command)
{
    std::string     irccommands[COMMANDS_COUNT] = {
        "PASS",
        "NICK",
        "USER",
        "OPER",
        "QUIT",
        "JOIN",
        "PART",
        "MODE",
        "TOPIC",
        "LIST",
        "INVITE",
        "KICK",
        "PRIVMSG"
    };
    
    for (int nn = 0 ; nn < COMMANDS_COUNT ; nn ++)
    {
        if (irccommands[nn] == command.getCommand())
        {
            (this->*executors[nn])(command);
            break;
        }
    }
}
