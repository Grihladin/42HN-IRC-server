/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:51:36 by macbook           #+#    #+#             */
/*   Updated: 2025/07/26 11:05:50 by psenko           ###   ########.fr       */
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
            deleteUserFromChannel((*iter).value, command.getUserFd());
        }
    }
    return (0);
}
