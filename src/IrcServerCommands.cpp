/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServerCommands.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:40:56 by psenko            #+#    #+#             */
/*   Updated: 2025/07/24 15:10:50 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/IrcServer.hpp"

void IrcServer::ircCommandPass(Command& command)
{
    std::cout << "Executor: " << command.getCommand() << std::endl;
}

void IrcServer::ircCommandNick(Command& command)
{
    std::cout << "Executor: " << command.getCommand() << std::endl;
}

void IrcServer::ircCommandUser(Command& command)
{
    std::cout << "Executor: " << command.getCommand() << std::endl;
}

void IrcServer::ircCommandOper(Command& command)
{
    std::cout << "Executor: " << command.getCommand() << std::endl;
}

void IrcServer::ircCommandQuit(Command& command)
{
    std::cout << "Executor: " << command.getCommand() << std::endl;
}

void IrcServer::ircCommandJoin(Command& command)
{
    std::cout << "Executor: " << command.getCommand() << std::endl;
}

void IrcServer::ircCommandPart(Command& command)
{
    std::cout << "Executor: " << command.getCommand() << std::endl;
}

void IrcServer::ircCommandMode(Command& command)
{
    std::cout << "Executor: " << command.getCommand() << std::endl;
}

void IrcServer::ircCommandTopic(Command& command)
{
    std::cout << "Executor: " << command.getCommand() << std::endl;
}

void IrcServer::ircCommandList(Command& command)
{
    std::cout << "Executor: " << command.getCommand() << std::endl;
}

void IrcServer::ircCommandInvite(Command& command)
{
    std::cout << "Executor: " << command.getCommand() << std::endl;
}

void IrcServer::ircCommandKick(Command& command)
{
    std::cout << "Executor: " << command.getCommand() << std::endl;
}

void IrcServer::ircCommandPrivMsg(Command& command)
{
    std::cout << "Executor: " << command.getCommand() << std::endl;
}
