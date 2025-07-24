/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServerParser.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 10:56:53 by psenko            #+#    #+#             */
/*   Updated: 2025/07/24 18:25:25 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/IrcServer.hpp"
#include "../Include/Command.hpp"

const Command IrcServer::commandParser(std::string rawdata, int client_socket)
{
	Command newcommand;
	std::cout << "Parser: " << rawdata << std::endl;
	newcommand.setCommand("USER");
	std::vector<paramstruct> params = {
		{"value", "123123"},
	};
	newcommand.setParams(params);
    newcommand.setUserFd(client_socket);
	return (newcommand);

    // Command     newcommand;
	// struct paramstruct newparam {"channel", "new"};
	// std::cout << "Parser: " << rawdata << std::endl;
	// newcommand.setCommand("JOIN");
	// newcommand.addParam(newparam);
	// return (newcommand);
}