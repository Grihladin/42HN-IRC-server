/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listenSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 09:38:31 by psenko            #+#    #+#             */
/*   Updated: 2025/07/30 10:12:29 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/IrcServer.hpp"

void IrcServer::listenSocket(void)
{
	poll_count = poll(socket_fds.data(), socket_fds.size(), -1);
	if (poll_count < 0)
	{
        if (errno == EINTR)
			return ;
		throw std::runtime_error("Error with poll!");
	}
	for (size_t i = 0; i < socket_fds.size(); ++i)
	{
		if (socket_fds[i].revents & POLLIN)
		{
			if (socket_fds[i].fd == server_fd)
			{
				client_len = sizeof(client_addr);
				client_fd = accept(server_fd,
						(struct sockaddr *)&client_addr, &client_len);
				if (client_fd < 0)
				{
					std::cerr << "Error accept connection" << std::endl;
					continue ;
				}
				fcntl(client_fd, F_SETFL, O_NONBLOCK);
				if (socket_fds.size() - 1 < MAX_CLIENTS)
				{
					std::cout << "New client connected. Socket: " << client_fd << std::endl;
					socket_fds.push_back({client_fd, POLLIN, 0});
				}
				else
				{
					std::cerr << "Max count of connections!" << std::endl;
					close(client_fd);
				}
			}
			else
			{
				if (handle_client(socket_fds[i].fd) != 0)
				{
					deleteUser(socket_fds[i].fd);
					closeUserFd(socket_fds[i].fd);
					i--;
				}
			}
		}
	}
}