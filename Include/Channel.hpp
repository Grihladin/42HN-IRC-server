/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 19:17:28 by psenko            #+#    #+#             */
/*   Updated: 2025/07/28 17:46:56 by mratke           ###   ########.fr       */
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
	std::vector<User*>			operators;
	std::vector<User*>			invitedUsers;
	std::vector<std::string> 	banMask;
	size_t 						userLimit = 0;
	std::string 				key;
	bool 						_inviteOnly;
	bool						_restrictTopic;
	bool						_isKey = false;

  public:
	Channel(const Channel &other) = default;
	Channel &operator=(const Channel &) = default;
	virtual ~Channel() = default;

	Channel(std::string name);
	std::string	getName(void) const;
	std::string	getTopic(void) const;
	const std::vector<User*> getUsers(void) const;
	const std::vector<std::string> getNickList();
	const std::string getNickListStr();
	int getUsersCount();
	size_t getUserLimit() const;
	
	int addUser(User* newuser);
	int addOperator(User* newuser);
	void delUserFromChannel(int user_fd);
	bool isUser(int user_fd);
	bool isUserOperator(int user_fd);
	bool isUserOnChannel(int user_fd);
	bool isKey(void);
	bool isInviteOnly(void);
	bool isRestrictTopic(void);
	int setTopic(std::string topic, int user_fd);
	int setKey(std::string newKey);
	void unsetKey(void);
	void setRestrictTopic(void);
	void unsetRestrictTopic(void);
	void setInviteOnly(void);
	void unsetInviteOnly(void);
	int setUserLimit(size_t newlimit);
};

#endif
