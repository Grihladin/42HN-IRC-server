/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:20:50 by psenko            #+#    #+#             */
/*   Updated: 2025/07/29 16:58:29 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/Channel.hpp"

Channel::Channel(std::string newname) : name(newname)
{
}

std::string Channel::getName(void) const
{
	return (name);
}

int Channel::addUser(User *newuser)
{
	if (newuser)
		users.push_back(newuser);
	return (0);
}

int Channel::addOperator(User *newuser)
{
	if (newuser && !isUserOperator(newuser->getSocketFd()))
	{
		std::cout << "Add operator to channel" << std::endl;
		operators.push_back(newuser);
	}
	return (0);
}

int Channel::deleteOperator(std::string username)
{
	if (operators.size() > 0)
	{
		std::vector<User *>::iterator iter;
		for (iter = operators.begin(); iter != operators.end(); ++iter)
		{
			if ((*iter)->getUserName() == username)
			{
				operators.erase(iter);
				break ;
			}
		}
	}
	return (0);
}

void Channel::delUserFromChannel(int user_fd)
{
	if (user_fd)
	{
		// Remove from users
		for (std::vector<User *>::iterator iter = users.begin(); iter != users.end(); ++iter)
		{
			if ((*iter)->getSocketFd() == user_fd)
			{
				users.erase(iter);
				std::cout << "User " << user_fd << " deleted from channel " << name << std::endl;
				break;
			}
		}

		// Remove from operators
		for (std::vector<User *>::iterator iter = operators.begin(); iter != operators.end(); ++iter)
		{
			if ((*iter)->getSocketFd() == user_fd)
			{
				operators.erase(iter);
				std::cout << "User " << user_fd << " removed from operators in channel " << name << std::endl;
				break;
			}
		}

		// Remove from invited users
		for (std::vector<User *>::iterator iter = invitedUsers.begin(); iter != invitedUsers.end(); ++iter)
		{
			if ((*iter)->getSocketFd() == user_fd)
			{
				invitedUsers.erase(iter);
				std::cout << "User " << user_fd << " removed from invited list in channel " << name << std::endl;
				break;
			}
		}
	}
}

bool Channel::isUser(int user_fd)
{
	for (std::vector<User *>::const_iterator it = users.begin(); it != users.end(); ++it)
	{
		if ((*it)->getSocketFd() == user_fd)
			return (true);
	}
	return (false);
}

bool Channel::isUserOnChannel(int user_fd)
{
	std::vector<User *>::iterator iter;
	for (iter = users.begin(); iter != users.end(); ++iter)
	{
		if ((*(*iter)).getSocketFd() == user_fd)
			return (true);
	}
	return (false);
}

bool Channel::isUserOnChannel(std::string nickname)
{
	for (User* iter : users)
	{
		if (iter->getNickName() == nickname)
			return (true);
	}
	return (false);
}

const std::vector<std::string> Channel::getNickList()
{
	std::vector<std::string> nickList;
	for (std::vector<User *>::iterator iter = users.begin(); iter != users.end(); ++iter)
	{
		nickList.push_back((*iter)->getNickName());
	}
	return (nickList);
}

const std::string Channel::getNickListStr()
{
	std::vector<std::string> nickList = getNickList();
	std::string result;
	for (std::vector<std::string>::iterator iter = nickList.begin(); iter != nickList.end(); ++iter)
	{
		if (result.length() > 0)
			result.append(",");
		result.append((*iter));
	}
	std::cout << "List of Nicknames: " << result << std::endl;
	return (result);
}

const std::vector<User *> Channel::getUsers(void) const
{
	return (users);
}
const std::vector<User *> Channel::getInvitedUsers(void) const
{
	return (invitedUsers);
}

std::string Channel::getTopic(void) const
{
	return (topic);
}

int Channel::getUsersCount()
{
	return (users.size());
}

bool Channel::isKey(void)
{
	return (_isKey);
}

bool Channel::isInviteOnly(void)
{
	return (_inviteOnly);
}

bool Channel::isRestrictTopic(void)
{
	return (_restrictTopic);
}

void Channel::setKey(std::string newKey)
{
	if (newKey.length() > 0)
	{
		_isKey = true;
		key = newKey;
	}
}

void Channel::unsetKey(void)
{
	_isKey = false;
	key.clear();
}

void Channel::setRestrictTopic(void)
{
	_restrictTopic = true;
}

void Channel::unsetRestrictTopic(void)
{
	_restrictTopic = false;
}

void Channel::setInviteOnly(void)
{
	_inviteOnly = true;
}

void Channel::unsetInviteOnly(void)
{
	_inviteOnly = false;
}

size_t Channel::getUserLimit() const
{
	return (userLimit);
}

void Channel::setUserLimit(size_t new_value)
{
	userLimit = new_value;
}

bool Channel::isUserOperator(int user_fd)
{
	for (std::vector<User *>::iterator it = operators.begin(); it != operators.end(); ++it)
	{
		if ((*it)->getSocketFd() == user_fd)
			return (true);
	}
	return (false);
}

int Channel::setTopic(std::string topic, int user_fd)
{
	(void)user_fd;
	this->topic = topic;
	return (0);
}

std::string Channel::getKey(void) const
{
	return (key);
}

void Channel::addInvitedUser(User* user)
{
    for (size_t i = 0; i < invitedUsers.size(); ++i)
    {
        if (invitedUsers[i] == user)
            return; // already invited
    }
    invitedUsers.push_back(user);
}

bool Channel::isUserInvited(User* user) const
{
    for (size_t i = 0; i < invitedUsers.size(); ++i)
    {
        if (invitedUsers[i] == user)
            return true;
    }
    return false;
}

void Channel::removeInvitedUser(User* user)
{
    for (std::vector<User*>::iterator it = invitedUsers.begin(); it != invitedUsers.end(); ++it)
    {
        if (*it == user)
        {
            invitedUsers.erase(it);
            break;
        }
    }
}

std::string Channel::getMode()
{
	std::string mode("");

	if (_inviteOnly)
		mode.append("i");
	if (_restrictTopic)
		mode.append("t");
	if (_isKey)
		mode.append("k");
	if (userLimit > 0)
		mode.append("l");
	return (mode);
}
