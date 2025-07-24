/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:51:58 by macbook           #+#    #+#             */
/*   Updated: 2025/07/24 16:52:27 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/IrcServer.hpp"

void IrcServer::ircCommandPass(Command& command)
{
    std::cout << "Executor: " << command.getCommand() << std::endl;
}