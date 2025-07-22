/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 13:26:40 by psenko            #+#    #+#             */
/*   Updated: 2025/07/22 17:53:45 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include <list>

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
                               } while (0)
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 10

int handle_client(int client_socket)
{
    char buffer[1024] = {0};
    int bytes_received = read(client_socket, buffer, 1024);
    if (bytes_received > 0)
    {
        std::cout << "Message from socket " << client_socket << ": " << buffer << std::endl;
        std::string response = "Responce.\n";
        send(client_socket, response.c_str(), response.length(), 0);
    }
    else
    {
        std::cout << "Client (socket " << client_socket << ") is disconnected or with error." << std::endl;
        return (-1);
    }
    return (0);
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cerr << "Wrong count of parameters. I need at least a port and a password." << std::endl;
        return 1;
    }

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1)
    {
        std::cerr << "Error creation of socket." << std::endl;
        return 1;
    }

    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        std::cerr << "setsockopt" << std::endl;
        close(server_fd);
        return 1;
    }
    fcntl(server_fd, F_SETFL, O_NONBLOCK);

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(std::stoi(std::string(argv[1])));

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        std::cerr << "Error of binding" << std::endl;
        close(server_fd);
        return 1;
    }

    if (listen(server_fd, 3) < 0)
    {
        std::cerr << "Error of listen" << std::endl;
        close(server_fd);
        return 1;
    }

    std::cout << "Wait for connections..." << std::endl;

    std::vector<struct pollfd> fds;
    fds.push_back({server_fd, POLLIN, 0});

    while (true)
    {
        int poll_count = poll(fds.data(), fds.size(), -1);
        
        if (poll_count < 0)
        {
            std::cerr << "poll" << std::endl;
            break;
        }

        for (size_t i = 0; i < fds.size(); ++i)
        {
            if (fds[i].revents & POLLIN)
            {
                if (fds[i].fd == server_fd)
                {
                    sockaddr_in client_addr;
                    socklen_t client_len = sizeof(client_addr);
                    int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);

                    if (client_fd < 0)
                    {
                        std::cerr << "Error accept connection" << std::endl;
                        continue;
                    }
                    fcntl(client_fd, F_SETFL, O_NONBLOCK);
                    if (fds.size() - 1 < MAX_CLIENTS) {
                        std::cout << "New client connected. Socket: " << client_fd << std::endl;
                        fds.push_back({client_fd, POLLIN, 0});
                    } else {
                        std::cerr << "Max count of connections!" << std::endl;
                        close(client_fd);
                    }
                }
                else
                {
                    if (handle_client(fds[i].fd) != 0)
                    {
                        close(fds[i].fd);
                        fds.erase(fds.begin() + i);
                        i--;
                    }
                }
            }
        }
    }
    close(server_fd);

    return 0;
}
