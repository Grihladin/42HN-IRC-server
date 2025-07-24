/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 11:27:49 by psenko            #+#    #+#             */
/*   Updated: 2025/07/24 12:08:07 by psenko           ###   ########.fr       */
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
# include "Command.hpp"

#define BUFFER_SIZE 10240
#define MAX_CLIENTS 10240
#define COMMANDS_COUNT 14

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
        int addUser();
        int addChannel();
        int sendMessageToChannel();
        int sendMessageToUser();
		const Command commandParser(std::string rawdata);
		void commandExecutor(Command& command);

		//Methods for IRC commands
		void ircCommandPass(Command& command);
		void ircCommandNick(Command& command);
		void ircCommandUser(Command& command);
		void ircCommandOper(Command& command);
		void ircCommandQuit(Command& command);
		void ircCommandJoin(Command& command);
		void ircCommandPart(Command& command);
		void ircCommandMode(Command& command);
		void ircCommandTopic(Command& command);
		void ircCommandList(Command& command);
		void ircCommandInvite(Command& command);
		void ircCommandKick(Command& command);
		void ircCommandPrivMsg(Command& command);
		void (IrcServer::*executors[COMMANDS_COUNT])(Command& command) = {\
			&IrcServer::ircCommandPass,
			&IrcServer::ircCommandNick,
			&IrcServer::ircCommandUser,
			&IrcServer::ircCommandOper,
			&IrcServer::ircCommandQuit,
			&IrcServer::ircCommandJoin,
			&IrcServer::ircCommandPart,
			&IrcServer::ircCommandMode,
			&IrcServer::ircCommandTopic,
			&IrcServer::ircCommandList,
			&IrcServer::ircCommandInvite,
			&IrcServer::ircCommandKick,
			&IrcServer::ircCommandPrivMsg
		};
	public:
		IrcServer(void);
		IrcServer(const IrcServer& other);
		IrcServer &operator=(const IrcServer &other);
		virtual ~IrcServer();
		
        IrcServer(std::string port, std::string password);
        void listenSocket(void);
};

#endif