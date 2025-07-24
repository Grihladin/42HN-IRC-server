/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServerCommandExecutor.cpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:11:44 by psenko            #+#    #+#             */
/*   Updated: 2025/07/24 12:34:51 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/IrcServer.hpp"

void IrcServer::commandExecutor(Command& command)
{
    for (int nn = 0 ; nn < COMMANDS_COUNT ; nn ++)
    {
        if (irccommands[nn] == command.getCommand())
        {
            (this->*executors[nn])(command);
            break;
        }
    }
}
