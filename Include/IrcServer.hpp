/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 11:27:49 by psenko            #+#    #+#             */
/*   Updated: 2025/07/23 20:50:00 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCSERVER_HPP
# define IRCSERVER_HPP

# include <string>
# include <iostream>
# include <vector>
# include <cstring>
# include <fcntl.h>
# include <unistd.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <poll.h>
# include "User.hpp"
# include "Message.hpp"
# include "Channel.hpp"

#define BUFFER_SIZE 10240
#define MAX_CLIENTS 10240

class IrcServer
{
	private:
        int                         server_fd;
        std::vector<struct pollfd>  socket_fds;
        std::vector<User>           users;
        std::vector<Message>        messages;
        std::vector<Channel>        channels;
        char                        buffer[BUFFER_SIZE] = {0};
        std::string                 password;
        
        int openSocket(std::string port);
        int handle_client(int client_socket);
        int addUser(int client_fd);
        int addChannel();
        int sendMessageToChannel();
        int sendMessageToUser();

		//Methods for IRC commands
		std::string ircCommandPass(const char* buffer, User* currentUser);
		void ircCommandNick();
		void ircCommandUser();
		void ircCommandOper();
		void ircCommandQuit();
		void ircCommandJoin();
		void ircCommandPart();
		void ircCommandMode();
		void ircCommandTopic();
		void ircCommandList();
		void ircCommandInvite();
		void ircCommandKick();
		void ircCommandPrivMsg();
	public:
		IrcServer(void);
		IrcServer(const IrcServer& other);
		IrcServer &operator=(const IrcServer &other);
		virtual ~IrcServer();
		
        IrcServer(std::string port, std::string password);
        void listenSocket(void);
		//Getters
		User* getUserByFd(int fd);
};

#endif