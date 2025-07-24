/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:48:47 by macbook           #+#    #+#             */
/*   Updated: 2025/07/24 16:49:47 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/IrcServer.hpp"

void IrcServer::ircCommandList(Command& command)
{
    std::cout << "Executor: " << command.getCommand() << std::endl;
}