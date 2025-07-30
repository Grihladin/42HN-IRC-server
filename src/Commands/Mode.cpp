/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:49:21 by macbook           #+#    #+#             */
/*   Updated: 2025/07/30 12:49:50 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/IrcServer.hpp"

int IrcServer::ircCommandMode(Command& command)
{
    std::cout << "Executor: " << command.getCommand() << std::endl;
    User *user = getUserByFd(command.getUserFd());
    if (!user || !user->isRegistered())
	{
		sendToFd(command.getUserFd(), ERR_NOTREGISTERED());
		return (1);
	}
    const std::vector<paramstruct> &params = command.getParams();
    if (params.size() == 0) {
        sendToFd(user->getSocketFd(), ERR_NEEDMOREPARAMS(user->getNickName(), command.getCommand()));
        return (1);
    }
    std::string recipient = params[0].value;
    std::string modes;
    if (params.size() > 1)
    {
        modes = params[1].value;
        if (modes.length() > 4)
        {
            std::cerr << "No more than 3 modes at a time!" << std::endl;
            return (1);
        }
    }
    if (recipient[0] == '#')
    {
        if (params.size() == 1)
        {
            sendToFd(command.getUserFd(), \
                RPL_CHANNELMODEIS(user->getNickName(), recipient, getChannelByName(recipient)->getMode(), ""));
            return (0);
        }
        Channel *channel = getChannelByName(recipient);
        if (channel && channel->isUserOperator(user->getSocketFd()))
        {
            if (modes[0] == '+')
            {
                if (modes[1] == 'i')
                    channel->setInviteOnly();
                else if (modes[1] == 't')
                    channel->setRestrictTopic();
                else if (modes[1] == 'k')
                {
                    if (params.size() < 3)
                    {
                        sendToFd(command.getUserFd(), ERR_NEEDMOREPARAMS(user->getNickName(), command.getCommand()));
                        return (1);
                    }
                    channel->setKey(params[2].value);
                }
                else if (modes[1] == 'o')
                {
                    if (params.size() < 3)
                    {
                        sendToFd(command.getUserFd(), ERR_NEEDMOREPARAMS(user->getNickName(), command.getCommand()));
                        return (1);
                    }
                    if (channel->isUserOnChannel(params[2].value))
                        channel->addOperator(getUserByNick(params[2].value));
                    else
                        sendToFd(command.getUserFd(), ERR_USERNOTINCHANNEL(user->getNickName(), params[2].value, recipient));
                }
                else if (modes[1] == 'l')
                    channel->setUserLimit(stoi(params[2].value));
                else
                {
                    sendToFd(command.getUserFd(), ERR_UNKNOWNMODE(user->getNickName(), modes[0], recipient));
                    return (1);
                }
            }
            else if (modes[0] == '-')
            {
                if (modes[1] == 'i')
                    channel->unsetInviteOnly();
                else if (modes[1] == 't')
                    channel->unsetRestrictTopic();
                else if (modes[1] == 'k')
                    channel->unsetKey();
                else if (modes[1] == 'o')
                    channel->deleteOperator(params[2].value);
                else if (modes[1] == 'l')
                    channel->setUserLimit(0);
                else
                {
                    sendToFd(command.getUserFd(), ERR_UNKNOWNMODE(user->getNickName(), modes[0], recipient));
                    return (1);
                }
            }
            else if (modes[0] == 'b')
            {
                sendToFd(command.getUserFd(), RPL_ENDOFBANLIST(user->getNickName(), recipient));
                return (0);
            }
            sendRawMessageToChannel(recipient, RPL_CHANGE_MODE(user->getNickName(), "", "server", command.getRawCommand()));
        }
        else if (modes[0] == 'b')
        {
            sendToFd(command.getUserFd(), RPL_ENDOFBANLIST(user->getNickName(), recipient));
            return (0);
        }
        else
            sendToFd(command.getUserFd(), ERR_CHANOPRIVSNEEDED(user->getNickName(), recipient));
    }
    else
    {
        //MODE for user
        ;
    }
    return (0);
}