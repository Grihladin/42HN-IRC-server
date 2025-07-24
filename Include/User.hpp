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