/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:51:36 by macbook           #+#    #+#             */
/*   Updated: 2025/07/24 16:51:54 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/IrcServer.hpp"

void IrcServer::ircCommandPart(Command& command)
{
    std::cout << "Executor: " << command.getCommand() << std::endl;
}