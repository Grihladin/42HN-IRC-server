/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 11:33:58 by psenko            #+#    #+#             */
/*   Updated: 2025/07/26 13:21:54 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/Definitions.hpp"
#include "../Include/IrcServer.hpp"

void	printParams(const std::vector<paramstruct> &params)
{
	for (const auto &param : params)
	{
		std::cout << param.name << ": " << param.value << "\n";
	}
}

int IrcServer::handle_client(int client_socket)
{
	int		bytes_received;
	size_t	spos;
	Command	newcommand;

	std::string result;
	while (result.empty() || result.back() != '\n')
	{
		memset(buffer, 0, BUFFER_SIZE);
		bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
		if (bytes_received > 0)
			result.append(buffer);
		else
		{
			std::cout << "Client (socket " << client_socket << ") is disconnected or with error." << std::endl;
			return (-1);
		}
	}
	std::cout << "Command from client: " << result << std::endl;
	while (result.length() > 0)
	{
		spos = result.find("\r\n");
		spos += 2;
		std::string strcommand = result.substr(0, spos);
		try
		{
			Command newcommand = commandParser(strcommand, client_socket);
			commandExecutor(newcommand);
		}
		catch (const std::exception &e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}
		result = result.substr(spos);
	}
	return (0);
}

IrcServer::IrcServer(void)
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
	close(server_fd);
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
}

void IrcServer::listenSocket(void)
{
	int			poll_count;
	sockaddr_in	client_addr;
	socklen_t	client_len;
	int			client_fd;

	while (true)
	{
		poll_count = poll(socket_fds.data(), socket_fds.size(), -1);
		if (poll_count < 0)
		{
			throw std::runtime_error("Error with poll!");
		}
		for (size_t i = 0; i < socket_fds.size(); ++i)
		{
			if (socket_fds[i].revents & POLLIN)
			{
				if (socket_fds[i].fd == server_fd)
				{
					client_len = sizeof(client_addr);
					client_fd = accept(server_fd,
							(struct sockaddr *)&client_addr, &client_len);
					if (client_fd < 0)
					{
						std::cerr << "Error accept connection" << std::endl;
						continue ;
					}
					fcntl(client_fd, F_SETFL, O_NONBLOCK);
					if (socket_fds.size() - 1 < MAX_CLIENTS)
					{
						std::cout << "New client connected. Socket: " << client_fd << std::endl;
						socket_fds.push_back({client_fd, POLLIN, 0});
					}
					else
					{
						std::cerr << "Max count of connections!" << std::endl;
						close(client_fd);
					}
				}
				else
				{
					if (handle_client(socket_fds[i].fd) != 0)
					{
						close(socket_fds[i].fd);
						socket_fds.erase(socket_fds.begin() + i);
						i--;
					}
				}
			}
		}
	}
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
	size_t i = 0;
    while ((i < socket_fds.size()) && (socket_fds[i].fd != user_fd))
        ++i;
    if (i <= socket_fds.size())
    {
        close(socket_fds[i].fd);
        socket_fds.erase(socket_fds.begin() + i);
    }
	return (0);
}

int IrcServer::addUser(int client_fd)
{
	User	newUser;

	newUser.setSocketFd(client_fd);
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
			std::cout << "User deleted: " << client_fd << std::endl;
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
		if (it->getNickname() == nickname)
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
		return (0);
	}
	std::vector<Channel>::iterator iterCh;
	for (iterCh = channels.begin(); iterCh != channels.end(); ++iterCh)
	{
		if ((iterCh->getName() == channelname)
			&& (!iterCh->isUserOnChannel(client_fd)))
		{
			iterCh->addUser(getUserByFd(client_fd));
			return (&(*iterCh));
		}
	}
	return (nullptr);
}
