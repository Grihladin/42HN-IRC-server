/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 13:26:40 by psenko            #+#    #+#             */
/*   Updated: 2025/07/22 19:17:34 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <thread>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "ParsedCommand.hpp"

void handle_client(int client_socket)
{
    std::cout << "New client connected. Socket: " << client_socket << std::endl;

    char buffer[1024] = {0};
    while (std::string(buffer) != std::string("exit"))
    {
        memset(buffer, 0, sizeof(buffer));
        int bytes_received = read(client_socket, buffer, 1024);
        if (bytes_received <= 0) {
            std::cout << "Client (socket " << client_socket << ") is disconnected." << std::endl;
            break;
        }

        std::cout << "Message from client (socket " << client_socket << "): " << buffer << std::endl;
        
        std::string response = "Responce.\n";
        send(client_socket, response.c_str(), response.length(), 0);
    }
    close(client_socket);
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

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(std::stoi(std::string(argv[1])));

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        std::cerr << "Error of binding" << std::endl;
        return 1;
    }

    if (listen(server_fd, 3) < 0)
    {
        std::cerr << "Error of listen" << std::endl;
        return 1;
    }

    std::cout << "Wait for connections..." << std::endl;

    while (true)
    {
        sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        
        int client_socket = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
        if (client_socket < 0) {
            std::cerr << "Error accept connection" << std::endl;
            continue;
        }

        std::thread client_thread(handle_client, client_socket);
        client_thread.detach();
    }
    close(server_fd);

    return 0;
}
