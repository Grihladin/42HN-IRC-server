/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:47:21 by macbook           #+#    #+#             */
/*   Updated: 2025/07/24 16:35:14 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/IrcServer.hpp"
#include "../../Include/Command.hpp"

//Parameters: <channel>{,<channel>} [<key>{,<key>}]

void IrcServer::ircCommandJoin(Command& command)
{
    std::cout << "Executor: " << command.getCommand() << std::endl;
    std::vector<struct paramstruct> params = command.getParams();
    for (size_t nn = 0 ; nn < params.size() ; ++nn)
    {
        if (params[nn].name == std::string("channel"))
        {
            // users.push_back(*getUserByFd(command.getUserFd()));
        }
    }
}

