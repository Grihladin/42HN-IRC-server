/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:53:34 by macbook           #+#    #+#             */
/*   Updated: 2025/07/24 20:15:36 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/IrcServer.hpp"

int IrcServer::ircCommandUser(Command& command)
{
    //Check that user is authenticaated
    //add user name, real name, and hoste name
    //Return according message to the client
    std::cout << "Executor: " << command.getCommand() << std::endl;
    return (0);
}
