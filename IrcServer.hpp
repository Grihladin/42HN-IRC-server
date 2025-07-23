/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 11:27:49 by psenko            #+#    #+#             */
/*   Updated: 2025/07/23 11:56:46 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCSERVER_HPP
# define IRCSERVER_HPP

# include <string>
# include <iostream>
# include <vector>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
# include "User.hpp"

#define BUFFER_SIZE 10240
#define MAX_CLIENTS 10240

class IrcServer
{
	private:
        int server_fd;
        std::vector<struct pollfd>  socket_fds;
        std::string                 name;
        std::vector<std::string>    users;
        char buffer[BUFFER_SIZE] = {0};
        std::string                 password;
        int openSocket(std::string port);
        int handle_client(int client_socket);
	public:
		IrcServer(void);
		IrcServer(const IrcServer& other);
		IrcServer &operator=(const IrcServer &other);
		virtual ~IrcServer();
		
        IrcServer(std::string port, std::string password);
        void listenSocket(void);
};

#endif