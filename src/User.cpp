/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 22:47:06 by macbook           #+#    #+#             */
/*   Updated: 2025/07/25 01:02:56 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/User.hpp"

std::string User::getNickName()
{
	return (_nickname);
}

void User::setNickName(const std::string &nickname)
{
	// needs checking that if user with this nickname exists on server
	if (nickname.empty() || nickname.size() > 9)
	{
		throw std::invalid_argument("Nickname must be 1-9 characters long.");
	}
	for (char c : nickname)
	{
		if (!std::isalnum(c) && c != '_' && c != '-')
		{
			throw std::invalid_argument("Nickname contains invalid characters.");
		}
	}
	_nickname = nickname;
}

bool User::isAuthenticated(void) const
{
	return (_isAuthenticated);
}

void User::setSocketFd(int fd)
{
	_socketFd = fd;
}

int User::getSocketFd() const
{
	return (_socketFd);
}

void User::setAuthenticated()
{
	_isAuthenticated = true;
}

bool User::isRegistered() const
{
	return (!_realname.empty() && !_nickname.empty() && !_username.empty()
		&& !_hostname.empty());
}