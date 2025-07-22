/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 19:19:16 by psenko            #+#    #+#             */
/*   Updated: 2025/07/22 19:20:11 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

# include <string>
# include <iostream>
# include <vector>

class User
{
	private:
            
	public:
		User(void);
		User(const User& other);
		User &operator=(const User &other);
		virtual ~User();

		User(std::string name);
};

#endif