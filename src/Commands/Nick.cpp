/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:50:32 by macbook           #+#    #+#             */
/*   Updated: 2025/07/24 16:50:58 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/IrcServer.hpp"

void IrcServer::ircCommandNick(Command& command)
{
    std::cout << "Executor: " << command.getCommand() << std::endl;
}