/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 22:47:06 by macbook           #+#    #+#             */
/*   Updated: 2025/07/22 22:52:27 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

std::string Client::getNickName()
{
    return _nickname;
}

void Client::setNickName(const std::string &nickname)
{
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
