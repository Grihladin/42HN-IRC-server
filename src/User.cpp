/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 22:47:06 by macbook           #+#    #+#             */
/*   Updated: 2025/07/26 14:31:07 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/User.hpp"

// Setters
void User::setNickName(const std::string &nickname)
{
	_nickname = nickname;
}

void User::setSocketFd(int fd)
{
	_socketFd = fd;
}

void User::setAuthenticated()
{
	_isAuthenticated = true;
}

int User::setUsername(std::string username)
{
	_username = username;
	return (0);
}

int User::setNickname(std::string nickname)
{
	_nickname = nickname;
	return (0);
}

int User::setRealname(std::string realname)
{
	_realname = realname;
	return (0);
}

int User::setRegistered()
{
	_isRegistered = true;
	return (0);
}

int User::setOperator(bool mode)
{
	_isOperator = mode;
	return (0);
}

// Getters
bool User::isRegistered() const
{
	return (!_realname.empty() && !_nickname.empty() && !_username.empty());
}

bool User::isAuthenticated() const
{
	return (_isAuthenticated);
}

int User::getSocketFd() const
{
	return (_socketFd);
}

std::string User::getUserName() const
{
	return (_username);
}

std::string User::getNickName(void) const
{
	return (_nickname);
}

std::string User::getRealName() const
{
	return (_realname);
}

bool User::isOperator() const
{
	return (_isOperator);
}