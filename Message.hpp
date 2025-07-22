/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 18:56:24 by psenko            #+#    #+#             */
/*   Updated: 2025/07/22 19:02:52 by psenko           ###   ########.fr       */
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
		Message(void);
		Message(const Message& other);
		Message &operator=(const Message &other);
		virtual ~Message();

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