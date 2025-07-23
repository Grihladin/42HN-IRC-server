/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 22:47:06 by macbook           #+#    #+#             */
/*   Updated: 2025/07/23 16:29:41 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

std::string User::getNickName()
{
    return _nickname;
}

void User::setNickName(const std::string &nickname)
{
    //needs checking that if user with this nickname exists on server
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
