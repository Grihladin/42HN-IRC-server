#pragma once
#include <cstddef>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

class Client
{
  public:
	Client();
    void setNickName(std::string NickName);


  private:
	std::string _NickName;
};