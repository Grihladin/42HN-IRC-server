/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 22:47:06 by macbook           #+#    #+#             */
/*   Updated: 2025/07/28 18:58:05 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/User.hpp"

User::User(int socket_fd) : _socketFd(socket_fd)
{
}

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

std::string User::getPrefix() const
{
	return (_nickname + "!" + _username + "@" + _hostname);
}

std::string User::getHostName(void) const
{
	return (_hostname);
}