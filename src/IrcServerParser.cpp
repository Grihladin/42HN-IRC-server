/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServerParser.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 10:56:53 by psenko            #+#    #+#             */
/*   Updated: 2025/07/24 23:42:21 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/IrcServer.hpp"
#include "../Include/Command.hpp"

const Command IrcServer::commandParser(std::string rawdata, int client_socket)
{
	Command newcommand = Command::parse(rawdata);
	newcommand.setUserFd(client_socket);
	// std::cout << "Parser: " << rawdata << std::endl;
	// newcommand.setCommand("USER");
	// std::vector<paramstruct> params = {
	// 	{"value", "123123"},
	// };
	// newcommand.setParams(params);
    // newcommand.setUserFd(client_socket);
	
	return (newcommand);
}