/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:53:16 by macbook           #+#    #+#             */
/*   Updated: 2025/07/24 16:53:30 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/IrcServer.hpp"

void IrcServer::ircCommandTopic(Command& command)
{
    std::cout << "Executor: " << command.getCommand() << std::endl;
}
