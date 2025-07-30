/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleClient.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:17:24 by psenko            #+#    #+#             */
/*   Updated: 2025/07/30 16:36:27 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/IrcServer.hpp"

int IrcServer::handle_client(int client_socket)
{
	int		bytes_received;
	size_t	spos;
	Command	newcommand;
	int		tries = 10;

	std::string result;
	while ((result.empty() || (result.back() != '\n')) && (tries))
	// while ((result.empty() || (result.back() != '\n')))
	{
		memset(buffer, 0, BUFFER_SIZE);
		bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
		if (bytes_received > 0)
			result.append(buffer);
		else if (bytes_received == 0)
		{
			std::cout << "Client (socket " << client_socket << ") is disconnected or with error." << std::endl;
			return (-1);
		}
		--tries;
	}
	std::cout << "Command from client: " << result << std::endl;
	while (result.length() > 0)
	{
		std::string strcommand;
		spos = result.find("\r\n");
		if (spos == std::string::npos)
			strcommand = result;
		else
		{
			spos += 2;
			strcommand = result.substr(0, spos);
		}
		try
		{
			Command newcommand = commandParser(strcommand, client_socket);
			commandExecutor(newcommand);
		}
		catch (const std::exception &e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}
		if (spos == std::string::npos)
			break ;
		result = result.substr(spos);
	}
	return (0);
}
