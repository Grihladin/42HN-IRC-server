/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 18:56:24 by psenko            #+#    #+#             */
/*   Updated: 2025/07/23 16:55:47 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include <string>
# include <iostream>

class Message
{
	private:
        std::string     content;
		std::string		user_from;
        std::string		user_to;
        int             connect_fd;
	public:
		Message(void) = default;
		Message(const Message& other) = default;
		Message &operator=(const Message &other) = default;
		virtual ~Message() = default;

		Message(std::string user_from, std::string user_to, std::string content);
        void setContent(std::string content);
        void setUserFrom(std::string user_from);
        void setUserTo(std::string user_to);
        void setConnectFd(int fd);
        const std::string getContent(void) const;
        const std::string getUserFrom(void) const;
        const std::string getUserTo(void) const;
        int getConnectFd(void);
};

#endif