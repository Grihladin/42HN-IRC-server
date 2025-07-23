/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 19:17:28 by psenko            #+#    #+#             */
/*   Updated: 2025/07/22 19:24:57 by psenko           ###   ########.fr       */
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
		Channel(void);
		Channel(const Channel& other);
		Channel &operator=(const Channel &other);
		virtual ~Channel();

		Channel(std::string name);

};

#endif