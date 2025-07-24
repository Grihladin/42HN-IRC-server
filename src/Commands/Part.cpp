/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:51:36 by macbook           #+#    #+#             */
/*   Updated: 2025/07/24 16:45:58 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/IrcServer.hpp"

// Parameters: <channel>{,<channel>}

void IrcServer::ircCommandPart(Command& command)
{
    std::cout << "Executor: " << command.getCommand() << std::endl;
    std::vector<struct paramstruct> params = command.getParams();
    std::vector<struct paramstruct>::iterator iter;
    for (iter = params.begin() ; iter != params.end() ; ++iter)
    {
        if ((*iter).name == std::string("channel"))
        {
            std::vector<Channel>::iterator iterCh;
            for (iterCh = channels.begin() ; iterCh != channels.end() ; ++iterCh)
            {
                if ((*iterCh).getName() == (*iter).value)
                {
                    (*iterCh).delUserFromChannel(command.getUserFd());
                    break;
                }
            }
            // users.push_back(*getUserByFd(command.getUserFd()));
        }
    }
}