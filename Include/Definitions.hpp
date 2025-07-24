/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Definitions.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 00:37:03 by auplisas          #+#    #+#             */
/*   Updated: 2025/07/25 00:51:47 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINITIONS_HPP
# define DEFINITIONS_HPP

#define ERR_NEEDMOREPARAMS(command) (std::string(":server 461 ") + command + " :Not enough parameters\r\n")
#define ERR_ALREADYREGISTRED ":server 462 :You may not reregister\r\n"
#define ERR_PASSWDMISMATCH ":server 464 :Password incorrect\r\n"

#endif
