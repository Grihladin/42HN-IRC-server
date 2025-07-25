/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:20:50 by psenko            #+#    #+#             */
/*   Updated: 2025/07/25 11:32:13 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/Channel.hpp"

Channel::Channel(std::string newname) : name(newname)
{}

std::string	Channel::getName(void) const
{
    return (name);
}

int Channel::addUser(User* newuser)
{
    if (newuser)
    {
        std::cout << "Add user to channel" << std::endl;
    }
    return (0);
}

int Channel::addOperator(User* newuser)
{
    if (newuser)
    {
        std::cout << "Add operator to channel" << std::endl;
    }
    return (0);
}

void Channel::delUserFromChannel(int user_fd)
{
    if (user_fd)
    {
        std::cout << "Del user from channel" << std::endl;
    }
}

bool Channel::isUser(int user_fd)
{
    if (user_fd){}
    return (true);
}

bool Channel::isUserOnChannel(int user_fd)
{
    std::vector<User*>::iterator iter;
	for (iter = users.begin() ; iter != users.end() ; ++iter)
    {
        if ((*(*iter)).getSocketFd() == user_fd)
            return (1);
    }
    return (0);
}