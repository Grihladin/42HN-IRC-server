/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 11:33:58 by psenko            #+#    #+#             */
/*   Updated: 2025/07/31 19:03:22 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/Definitions.hpp"
#include "../Include/IrcServer.hpp"

void IrcServer::printParams(const std::vector<struct paramstruct> &params)
{
	for (const auto &param : params)
	{
		std::cout << param.name << ": " << param.value << "\n";
	}
}

IrcServer::IrcServer(void) //wrf?
{
	if (openSocket("6667"))
	{
		throw std::runtime_error("Error with creation IrcServer!");
	}
	password = "";
}

IrcServer::IrcServer(const IrcServer &other)
{
	*this = other;
}

IrcServer &IrcServer::operator=(const IrcServer &other)
{
	if (this != &other)
	{
		this->server_fd = other.server_fd;
		this->socket_fds = other.socket_fds;
		this->users = other.users;
		this->channels = other.channels;
		std::memcpy(this->buffer, other.buffer, BUFFER_SIZE);
		this->password = other.password;
	}
	return (*this);
}

IrcServer::~IrcServer()
{
	if (socket_fds.size() > 0)
	{
		for (std::vector<struct pollfd>::iterator iter = socket_fds.begin() ; iter != socket_fds.end() ; ++iter)
		{
			close((*iter).fd);
		}
	}
}

IrcServer::IrcServer(std::string port, std::string newpass)
{
	if (openSocket(port))
	{
		throw std::runtime_error("Error with creation IrcServer!");
	}
	password = newpass;
	//FOR DEBUG ADD CHANNELS
	for (int ii = 0; ii < 10; ++ii)
	{
		addChannel(std::string("#Channel").append(std::to_string(ii)));
	}
	Channel *chenel1 = getChannelByName("#Channel1");
	Channel *chenel2 = getChannelByName("#Channel2");
	Channel *chenel3 = getChannelByName("#Channel3");
	chenel1->setKey("1");
	chenel2->setKey("2");
	chenel3->setKey("3");

}

int IrcServer::openSocket(std::string port)
{
	int			opt;
	sockaddr_in	server_addr;

	opt = 1;
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd == -1)
	{
		std::cerr << "Error creation of socket." << std::endl;
		return (1);
	}
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
	{
		std::cerr << "setsockopt" << std::endl;
		close(server_fd);
		return (1);
	}
	fcntl(server_fd, F_SETFL, O_NONBLOCK);
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(std::stoi(std::string(port)));
	if (std::stoi(std::string(port)) < 1024 || std::stoi(std::string(port)) > 65535) //check for correct number
	{
		std::cerr << "Port number must be between 1024 and 65535." << std::endl;
		close(server_fd);
		return (1);
	}
	if (bind(server_fd, (struct sockaddr *)&server_addr,
			sizeof(server_addr)) < 0)
	{
		std::cerr << "Error of binding" << std::endl;
		close(server_fd);
		return (1);
	}
	if (listen(server_fd, 3) < 0)
	{
		std::cerr << "Error of listen" << std::endl;
		close(server_fd);
		return (1);
	}
	std::cout << "Wait for connections..." << std::endl;
	socket_fds.push_back({server_fd, POLLIN, 0});
	return (0);
}

int IrcServer::closeUserFd(int user_fd)
{
	std::vector<struct pollfd>::iterator iter;
	for (iter = socket_fds.begin(); iter != socket_fds.end() ; ++iter)
	{
		if ((*iter).fd == user_fd)
		{
			shutdown(user_fd, SHUT_WR);
			while (recv(user_fd, buffer, sizeof(buffer), 0) > 0)
				;
			close(user_fd);
			socket_fds.erase(iter);
			
			std::vector<struct buffer_struct>::iterator iterBuff;
			for (iterBuff = buffers.begin() ;
				((*iterBuff).user_fd != user_fd) && (iterBuff != buffers.end()) ; ++iterBuff) {}
			if (iterBuff != buffers.end())
				buffers.erase(iterBuff);
			break ;
		}
	}
	return (0);
}

int IrcServer::addUser(int client_fd)
{
	User	newUser(client_fd);

	// newUser.setSocketFd(client_fd);
	users.push_back(newUser);
	std::cout << "New user added with fd: " << client_fd << std::endl;
	return (0);
}

int IrcServer::deleteUser(int client_fd)
{
	std::list<User>::iterator iter;
	for (iter = users.begin(); iter != users.end(); ++iter)
	{
		if ((*iter).getSocketFd() == client_fd)
		{
			users.erase(iter);
			break ;
		}
	}
	return (0);
}

User *IrcServer::getUserByFd(int fd)
{
	std::list<User>::iterator iter;
	for (iter = users.begin(); iter != users.end(); ++iter)
	{
		if ((*iter).getSocketFd() == fd)
			return (&(*iter));
	}
	return (nullptr);
}

User *IrcServer::getUserByNick(std::string nickname) {
  for (User &user : users) {
    if (user.getNickName() == nickname)
      return &user;
  }
  return nullptr;
}

std::string IrcServer::getPassword() const
{
	return (password);
}

std::string IrcServer::getOperPassword() const
{
	return (operPassword);
}

bool IrcServer::isNicknameExist(std::string nickname)
{
	for (std::list<User>::iterator it = users.begin(); it != users.end(); ++it)
	{
		if (it->getNickName() == nickname)
			return (true);
	}
	return (false);
}

int IrcServer::addChannel(std::string newname)
{
	Channel newChannel(newname);
	channels.push_back(newChannel);
	std::cout << "New channel added: " << newname << std::endl;
	return (0);
}

int IrcServer::addChannel(std::string newname, int user_fd)
{
	Channel newChannel(newname);
	newChannel.addUser(getUserByFd(user_fd));
	newChannel.addOperator(getUserByFd(user_fd));
	channels.push_back(newChannel);
	std::cout << "New channel added: " << newname << std::endl;
	return (0);
}

bool IrcServer::isChannelExist(std::string chname)
{
	for (std::vector<Channel>::iterator iter = channels.begin(); iter != channels.end(); ++iter)
	{
		if (iter->getName() == chname)
			return (true);
	}
	return (false);
}

Channel *IrcServer::addUserToChannel(std::string channelname, int client_fd)
{
	if (!isChannelExist(channelname))
	{
		addChannel(channelname, client_fd);
		return (&channels.back());
	}
	for (Channel &iterCh : channels)
	{
		if ((iterCh.getName() == channelname)
			&& (!iterCh.isUserOnChannel(client_fd)))
		{
			iterCh.addUser(getUserByFd(client_fd));
			return (&iterCh);
		}
	}
	return (nullptr);
}
