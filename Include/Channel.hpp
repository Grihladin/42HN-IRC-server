/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 19:17:28 by psenko            #+#    #+#             */
/*   Updated: 2025/07/26 20:14:36 by auplisas         ###   ########.fr       */
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
	std::vector<std::string> 	banMask;
	// size_t 						limit;
	std::string 				key;
	// bool 						inviteOnly;

  public:
	Channel(const Channel &other) = default;
	Channel &operator=(const Channel &) = default;
	virtual ~Channel() = default;

	Channel(std::string name);
	std::string	getName(void) const;
	std::string	getTopic(void) const;
	const std::vector<std::string> getNickList();
	const std::string getNickListStr();
	int getUsersCount();
	
	int addUser(User* newuser);
	int addOperator(User* newuser);
	void delUserFromChannel(int user_fd);
	bool isUser(int user_fd);
	bool isUserOperator(int user_fd);
	bool isUserOnChannel(int user_fd);
	int setTopic(std::string topic, int user_fd);
};

#endif