/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:51:36 by macbook           #+#    #+#             */
/*   Updated: 2025/07/24 19:59:41 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/IrcServer.hpp"

// Parameters: <channel>{,<channel>}

int IrcServer::ircCommandPart(Command& command)
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
    return (0);
}