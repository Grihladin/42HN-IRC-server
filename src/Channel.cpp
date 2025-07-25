/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:20:50 by psenko            #+#    #+#             */
/*   Updated: 2025/07/25 16:12:49 by psenko           ###   ########.fr       */
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
        users.push_back(newuser);
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

const std::vector<std::string> Channel::getNickList()
{
    std::vector<std::string>    nickList;

    for (std::vector<User*>::iterator iter = users.begin() ; iter != users.end() ; ++iter)
    {
        nickList.push_back((*iter)->getNickName());
    }
    return (nickList);
}

const std::string Channel::getNickListStr()
{
    std::vector<std::string>    nickList = getNickList();
    std::string result;
    
    for (std::vector<std::string>::iterator iter = nickList.begin() ; iter != nickList.end() ; ++iter)
    {
        if (result.length() > 0)
            result.append(",");
        result.append((*iter));
    }
    std::cout << "List of Nicknames: " << result << std::endl;
    return (result);
}

std::string	Channel::getTopic(void) const
{
    return(topic);
}
