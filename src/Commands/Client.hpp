#pragma once
#include "Nickname.hpp"
#include <cstddef>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

class Client
{
  public:
	Client() = default;
	// Setters
	void setNickName(const std::string &nickname);
	// Getters
	std::string getNickName();

  private:
	std::string _nickname;
};