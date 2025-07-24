/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:48:19 by macbook           #+#    #+#             */
/*   Updated: 2025/07/24 21:08:24 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/IrcServer.hpp"

int IrcServer::ircCommandKick(Command& command)
{
    //Check that user exists
    //Then check that kicking user has operator rights global or on channel
    //we call kickUserFromChanel -> which calls deleteUserFromChannel which calls deleteuserfrom channel on channel class
    std::cout << "Executor: " << command.getCommand() << std::endl;
    return (0);
}