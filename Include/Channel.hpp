/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 19:17:28 by psenko            #+#    #+#             */
/*   Updated: 2025/07/23 18:06:49 by macbook          ###   ########.fr       */
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
	std::string name;
	std::string topic;
	std::vector<std::string> users;
	std::vector<std::string> operators;
	std::vector<std::string> banMask;
	size_t limit;
	std::string key;
	bool inviteOnly;

  public:
	Channel(const Channel &other) = default;
	Channel &operator=(const Channel &) = default;
	virtual ~Channel() = default;
	;

	Channel(std::string name);
};

#endif