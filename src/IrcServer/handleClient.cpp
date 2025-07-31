/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleClient.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:17:24 by psenko            #+#    #+#             */
/*   Updated: 2025/07/31 09:15:15 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/IrcServer.hpp"

int IrcServer::handle_client(int client_socket)
{
	int		bytes_received;
	size_t	spos;
	std::vector<struct buffer_struct>::iterator iterBuff;

	for (iterBuff = buffers.begin() ;
		((*iterBuff).user_fd != client_socket) && (iterBuff != buffers.end()) ; ++iterBuff) {}
	if (iterBuff == buffers.end())
		throw std::runtime_error("Error with buffer!");

	memset(buffer, 0, BUFFER_SIZE);
	bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
	if (bytes_received > 0)
		(*iterBuff).buffer.append(buffer);
	else if (bytes_received == 0)
	{
		std::cout << "Client (socket " << client_socket << ") is disconnected or with error." << std::endl;
		return (-1);
	}
	else
		return (0);
	spos = (*iterBuff).buffer.find("\r\n");
	// std::cout << "Buffer: " << (*iterBuff).buffer << std::endl;
	while (!(*iterBuff).buffer.empty() && (spos != std::string::npos))
	{
		std::string strcommand;
		spos += 2;
		strcommand = (*iterBuff).buffer.substr(0, spos);
		try
		{
			Command newcommand = commandParser(strcommand, client_socket);
			commandExecutor(newcommand);
		}
		catch (const std::exception &e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}
		if (getUserByFd(client_socket))
		{
			(*iterBuff).buffer = (*iterBuff).buffer.substr(spos);
			spos = (*iterBuff).buffer.find("\r\n");
			if (spos == std::string::npos)
				break ;
		}
		else
			break ;
	}
	return (0);
}
