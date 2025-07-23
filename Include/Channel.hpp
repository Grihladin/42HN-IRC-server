/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 19:17:28 by psenko            #+#    #+#             */
/*   Updated: 2025/07/23 16:55:17 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <string>
# include <iostream>
# include <vector>
# include "User.hpp"

class Channel
{
	private:
        std::string                 name;
        std::vector<std::string>    users;
	public:
		Channel(const Channel& other) = default;
		Channel& operator=(const Channel&) = default;
		virtual ~Channel() = default;;

		Channel(std::string name);

};

#endif