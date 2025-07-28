/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:03:05 by psenko            #+#    #+#             */
/*   Updated: 2025/07/28 17:08:52 by auplisas         ###   ########.fr       */
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
	User(int socket_fd);
	// Setters
	void setNickName(const std::string &nickname);
	void setSocketFd(int fd);
	void setAuthenticated();
	int setUsername(std::string username);
	int setNickname(std::string nickname);
	int setRealname(std::string realname);
	int setRegistered();
	int setOperator(bool mode);
	// Getters
	bool isRegistered() const; //Checks that realname, nickname, servername, hostname and username is entered
	bool isAuthenticated() const;
	int getSocketFd() const;
	std::string getUserName(void) const;
	std::string getNickName(void) const;
	std::string getRealName(void) const;
	bool isOperator(void) const;
	std::string getPrefix() const;
  private:
	int _socketFd;
	bool _isOperator = false;
	bool _isAuthenticated = false;
	bool _isRegistered = false;
	std::string _nickname;
	std::string _username;
	std::string _realname;
	std::string _hostname = "42Heilbronn";
};
