/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Definitions.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 00:37:03 by auplisas          #+#    #+#             */
/*   Updated: 2025/07/25 14:06:25 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINITIONS_HPP
# define DEFINITIONS_HPP

#define ERR_NEEDMOREPARAMS(command) (std::string(":server 461 ") + command + " :Not enough parameters\r\n")
#define ERR_ALREADYREGISTRED ":server 462 :You may not reregister\r\n"
#define ERR_PASSWDMISMATCH ":server 464 :Password incorrect\r\n"
#define ERR_UNKNOWNCOMMAND(nick, command) (std::string(":server 421 ") + nick + " " + command.erase(command.find_last_not_of("\r\n") + 1) + " :Unknown command\r\n")
#define ERR_NONICKNAMEGIVEN(nick) (std::string(":server 431 ") + nick + " :No nickname given\r\n")
#define ERR_ERRONEUSNICKNAME(nick, badnick) (std::string(":server 432 ") + nick + " " + badnick + " :Erroneous nickname\r\n")
#define ERR_NICKNAMEINUSE(nick, newnick) (std::string(":server 433 ") + nick + " " + newnick + " :Nickname is already in use\r\n")

#define RPL_WELCOME(nick) (std::string(":server 001 ") + nick + " :Welcome to the IRC server " + nick + "\r\n")

#define RPL_NOTOPIC ":server 331 :No topic is set\r\n"
#define RPL_TOPIC(channel, topic) (std::string(":server 332 ") + channel + " " + topic + "\r\n")

#endif
