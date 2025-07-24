/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:20:50 by psenko            #+#    #+#             */
/*   Updated: 2025/07/24 17:03:33 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/Channel.hpp"

std::string	Channel::getName(void) const
{
    return (name);
}

void Channel::addUserToChannel(int user_fd)
{
    if (user_fd)
    {
        std::cout << "Add user to channel" << std::endl;
    }
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
