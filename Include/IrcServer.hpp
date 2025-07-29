/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 11:27:49 by psenko            #+#    #+#             */
/*   Updated: 2025/07/29 15:39:37 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCSERVER_HPP
# define IRCSERVER_HPP

# include "Channel.hpp"
# include "Command.hpp"
# include "Message.hpp"
# include "User.hpp"
# include "Definitions.hpp"
# include <cstring>
# include <fcntl.h>
# include <iostream>
# include <list>
# include <netinet/in.h>
# include <poll.h>
# include <string>
# include <sys/socket.h>
# include <unistd.h>
# include <vector>

# define BUFFER_SIZE 10240
# define MAX_CLIENTS 10240
# define COMMANDS_COUNT 16

class IrcServer
{
	private:
        int                         server_fd;
        std::vector<struct pollfd>  socket_fds;
		int							poll_count;
		sockaddr_in					client_addr;
		socklen_t					client_len;
		int							client_fd;
        std::list<User>           	users;
        std::vector<Message>        messages;
        std::vector<Channel>        channels;
        char                        buffer[BUFFER_SIZE] = {0};
        std::string                 password;
		std::string operPassword = "424242";
        
        int openSocket(std::string port);
		int closeUserFd(int user_fd);
		int sendToFd(int user_fd, std::string message);
        int handle_client(int client_socket);
        int addUser();
		int addUser(int client_fd);
		int addUser(User newuser);
		int deleteUser(int client_fd);
        int addChannel();
		int addChannel(std::string newname);
		int addChannel(std::string newname, int user_fd);
        int sendMessageToChannel(int user_fd, std::string channel, std::string &message);
		int sendRawMessageToChannel(std::string channel, std::string reply);
        int sendMessageToUser(int user_fd, std::string user, std::string &message);
		const Command commandParser(std::string rawdata, int client_socket);
		void commandExecutor(Command &command);
		// bool isUserExist(int fd);
		// bool isUserExist(std::string nickname);
		bool isNicknameExist(std::string nickname);
		bool isChannelExist(std::string chname);
		//Getters
		std::string getPassword() const;
		std::string getOperPassword() const;
		bool isUserAuthenticated(int client_fd) const;
		bool isUserRegistered(int client_fd) const; //Checks that realname, nickname, servername, hostname and username is entered
		Channel* getChannelByName(std::string channelname);
		void printParams(const std::vector<struct paramstruct> &params);
		// const std::vector<Channel> &getChannelList() const;
		// const std::vector<Channel> getChannelList(std::vector<std::string>);
		User* getUserByFd(int fd);
		User* getUserByNick(std::string nickname);
		const std::vector<std::string> getNickList(std::string channelname);
		const std::string getNickListStr(std::string channelname);
		//Setters
		int setUsername(std::string username, int client_fd);
		int setNickname(std::string nickname, int client_fd); // Check unique nickname true or not return according error code
		int setRealname(std::string Realname, int client_fd);
		Channel *addUserToChannel(std::string channelname, int user_fd);
		int kickUserFromChannel(std::string channelname, std::string username);
		int deleteUserFromChannel(std::string channelname, int user_fd);
		int deleteUserFromAllChannels(int user_fd);
		int deleteUserFromServer(int user_fd); //It will go though channels, kick them out of there, send message to eveeryone
		int setTopicToChannel(std::string channelname, std::string topic, int user_fd);
		void connectIsSuccesfull(User *user);
		//Methods for IRC commands
		int ircCommandPass(Command& command);
		int ircCommandNick(Command& command);
		int ircCommandUser(Command& command);
		int ircCommandOper(Command& command);
		int ircCommandQuit(Command& command);
		int ircCommandJoin(Command& command);
		int ircCommandPart(Command& command);
		int ircCommandPing(Command& command);
		int ircCommandPong(Command& command);
		int ircCommandMode(Command& command);
		int ircCommandTopic(Command& command);
		int ircCommandList(Command& command);
		int ircCommandInvite(Command& command);
		int ircCommandKick(Command& command);
		int ircCommandPrivMsg(Command& command);
		int ircCommandWrong(Command& command);
		int (IrcServer::*executors[COMMANDS_COUNT])(Command &command) = {\
			&IrcServer::ircCommandPass,
			&IrcServer::ircCommandNick,
			&IrcServer::ircCommandUser,
			&IrcServer::ircCommandOper,
			&IrcServer::ircCommandQuit,
			&IrcServer::ircCommandJoin,
			&IrcServer::ircCommandPart,
			&IrcServer::ircCommandPing,
			&IrcServer::ircCommandPong,
			&IrcServer::ircCommandMode,
			&IrcServer::ircCommandTopic,
			&IrcServer::ircCommandList,
			&IrcServer::ircCommandInvite,
			&IrcServer::ircCommandKick,
			&IrcServer::ircCommandPrivMsg,
			&IrcServer::ircCommandWrong
		};

		std::string irccommands[COMMANDS_COUNT] = {
			"PASS",
			"NICK",
			"USER",
			"OPER",
			"QUIT",
			"JOIN",
			"PART",
			"PING",
			"PONG",
			"MODE",
			"TOPIC",
			"LIST",
			"INVITE",
			"KICK",
			"PRIVMSG",
			""
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
