/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 19:17:28 by psenko            #+#    #+#             */
/*   Updated: 2025/07/25 11:29:42 by psenko           ###   ########.fr       */
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
	size_t 						limit;
	std::string 				key;
	bool 						inviteOnly;

  public:
	Channel(const Channel &other) = default;
	Channel &operator=(const Channel &) = default;
	virtual ~Channel() = default;

	Channel(std::string name);
	std::string	getName(void) const;
	std::string	getTopic(void) const;
	
	int addUser(User* newuser);
	int addOperator(User* newuser);
	void delUserFromChannel(int user_fd);
	bool isUser(int user_fd);
	bool isUserOperator(int user_fd);
	bool isUserOnChannel(int user_fd);
	int setTopic(std::string topic, int user_fd);
};

#endif