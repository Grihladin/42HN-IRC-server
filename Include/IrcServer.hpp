/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 11:27:49 by psenko            #+#    #+#             */
/*   Updated: 2025/07/25 15:55:53 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCSERVER_HPP
# define IRCSERVER_HPP

# include <string>
# include <iostream>
# include <vector>
# include <list>
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
        std::list<User>           	users;
        std::vector<Message>        messages;
        std::vector<Channel>        channels;
        char                        buffer[BUFFER_SIZE] = {0};
        std::string                 password;
        
        int openSocket(std::string port);
        int handle_client(int client_socket);
        int addUser();
		int addUser(int client_fd);
		int addUser(User newuser);
		int deleteUser(int client_fd);
        int addChannel();
		int addChannel(std::string newname, int user_fd);
        int sendMessageToChannel(Message &message);
        int sendMessageToUser(Message &message);
		const Command commandParser(std::string rawdata, int client_socket);
		void commandExecutor(Command& command);
		bool isUserExist(int fd);
		bool isUserExist(std::string username);
		bool isNicknameExist(std::string nickname);
		bool isChannelExist(std::string chname);
		//Getters
		std::string getPassword() const;
		bool isUserAuthenticated(int client_fd) const;
		bool isUserRegistered(int client_fd) const; //Checks that realname, nickname, servername, hostname and username is entered
		Channel* getChannelByName(std::string channelname);
		const std::vector<Channel>& getChannelList() const;
		const std::vector<Channel> getChannelList(std::vector<std::string>) const;
		User* getUserByFd(int fd);
		const std::vector<std::string> getNickList(std::string channelname);
		const std::string getNickListStr(std::string channelname);
		//Setters
		int setUsername(std::string username, int client_fd);
		int setNickname(std::string nickname, int client_fd); // Check unique nickname true or not return according error code
		int setRealname(std::string Realname, int client_fd);
		int addUserToChannel(std::string channelname, int user_fd);
		int kickUserFromChannel(std::string channelname, std::string username);
		int deleteUserFromChannel(std::string channelname, int user_fd);
		int deleteUserFromServer(int user_fd); //It will go though channels, kick them out of there, send message to eveeryone
		int setTopicToChannel(std::string channelname, std::string topic, int user_fd);
		//Methods for IRC commands
		int ircCommandPass(Command& command);
		int ircCommandNick(Command& command);
		int ircCommandUser(Command& command);
		int ircCommandOper(Command& command);
		int ircCommandQuit(Command& command);
		int ircCommandJoin(Command& command);
		int ircCommandPart(Command& command);
		int ircCommandMode(Command& command);
		int ircCommandTopic(Command& command);
		int ircCommandList(Command& command);
		int ircCommandInvite(Command& command);
		int ircCommandKick(Command& command);
		int ircCommandPrivMsg(Command& command);
		int (IrcServer::*executors[COMMANDS_COUNT])(Command& command) = {\
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

		std::string irccommands[COMMANDS_COUNT] = {
			"PASS",
			"NICK",
			"USER",
			"OPER",
			"QUIT",
			"JOIN",
			"PART",
			"MODE",
			"TOPIC",
			"LIST",
			"INVITE",
			"KICK",
			"PRIVMSG"
		};
	public:
		IrcServer(void);
		IrcServer(const IrcServer& other);
		IrcServer &operator=(const IrcServer &other);
		virtual ~IrcServer();
		
        IrcServer(std::string port, std::string password);
        void listenSocket(void);
		//Getters
};

#endif