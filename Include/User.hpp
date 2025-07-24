/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:03:05 by psenko            #+#    #+#             */
/*   Updated: 2025/07/24 15:04:43 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <cstddef>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

class User
{
  public:
	User() = default;
	// Setters
	void setNickName(const std::string &nickname);
	void setSocketFd(int fd);
	void setAuthenticated();
	// Getters
	void setSocketFd(int fd);
	void setAuthenticated();
	std::string getNickName();
	bool isAuthenticated() const;
	int getSocketFd() const;

  private:
	int _socketFd;
	bool _isAuthenticated = false;
	std::string _nickname;
	std::string _username;
	std::string _hostname;
	std::string _servername;
	std::string _realname;
};
