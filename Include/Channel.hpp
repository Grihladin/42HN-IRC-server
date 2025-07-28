/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 19:17:28 by psenko            #+#    #+#             */
/*   Updated: 2025/07/28 17:08:21 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "User.hpp"
# include <iostream>
# include <string>
# include <vector>

class Channel
{
  	private:
		std::string 				name;
		std::string 				topic;
		std::vector<User*>		 	users;
		std::vector<User*>			operators;		//o
		std::vector<User*>			invitedUsers;
		std::vector<std::string> 	banMask;
		size_t 						userLimit = 0;	//l
		std::string 				key;
		bool 						_inviteOnly;	//i
		bool						_restrictTopic;	//t
		bool						_isKey = false;	//k
	
	public:
		Channel(const Channel &other) = default;
		Channel &operator=(const Channel &) = default;
		virtual ~Channel() = default;

		Channel(std::string name);
		std::string	getName(void) const;
		std::string	getTopic(void) const;
		std::string getKey(void) const;
		const std::vector<User*> getUsers(void) const;
		const std::vector<std::string> getNickList();
		const std::string getNickListStr();
		int getUsersCount();
		size_t getUserLimit() const;
		
		int addUser(User* newuser);
		int addOperator(User* newuser);
		int deleteOperator(std::string username);
		void delUserFromChannel(int user_fd);
		bool isUser(int user_fd);
		bool isUserOperator(int user_fd);
		bool isUserOnChannel(int user_fd);
		bool isKey(void);
		bool isInviteOnly(void);
		bool isRestrictTopic(void);
		int setTopic(std::string topic, int user_fd);
		void setKey(std::string newKey);
		void unsetKey(void);
		void setRestrictTopic(void);
		void unsetRestrictTopic(void);
		void setInviteOnly(void);
		void unsetInviteOnly(void);
		void setUserLimit(size_t new_value);
};

#endif