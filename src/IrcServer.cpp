/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 11:33:58 by psenko            #+#    #+#             */
/*   Updated: 2025/07/24 12:12:19 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/IrcServer.hpp"

int IrcServer::handle_client(int client_socket)
{
    memset(buffer, 0, BUFFER_SIZE);
    int bytes_received = read(client_socket, buffer, BUFFER_SIZE);
    if (bytes_received > 0)
    {
        std::cout << "Message from socket " << client_socket << ": " << buffer << std::endl;
        std::string response = "Responce.\n";
        // send(client_socket, response.c_str(), response.length(), 0);
        Command newcommand = commandParser(std::string(buffer));
        commandExecutor(newcommand);
    }
    else
    {
        std::cout << "Client (socket " << client_socket << ") is disconnected or with error." << std::endl;
        return (-1);
    }
    return (0);
}

IrcServer::IrcServer(void)
{
    if (openSocket("6667"))
    {
        throw std::runtime_error("Error with creation IrcServer!");
    }
    password = "";
}

IrcServer::IrcServer(const IrcServer& other)
{
    *this = other;
}
IrcServer& IrcServer::operator=(const IrcServer &other)
{
    if (this != &other)
    {
        this->server_fd = other.server_fd;
        this->socket_fds = other.socket_fds;
        this->users = other.users;
        this->channels = other.channels;
        std::memcpy(this->buffer, other.buffer, BUFFER_SIZE);
        this->password = other.password;
    }
    return *this;
}

IrcServer::~IrcServer()
{
    close(server_fd);
}

IrcServer::IrcServer(std::string port, std::string newpass)
{
    if (openSocket(port))
    {
        throw std::runtime_error("Error with creation IrcServer!");
    }
    password = newpass;
}

void IrcServer::listenSocket(void)
{
    while (true)
    {
        int poll_count = poll(socket_fds.data(), socket_fds.size(), -1);
        
        if (poll_count < 0)
        {
            std::cerr << "poll" << std::endl;
            break;
        }

        for (size_t i = 0; i < socket_fds.size(); ++i)
        {
            if (socket_fds[i].revents & POLLIN)
            {
                if (socket_fds[i].fd == server_fd)
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
                        close(socket_fds[i].fd);
                        socket_fds.erase(socket_fds.begin() + i);
                        i--;
                    }
                }
            }
        }
    }
}

int IrcServer::openSocket(std::string port)
{
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1)
    {
        std::cerr << "Error creation of socket." << std::endl;
        return 1;
    }
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        std::cerr << "setsockopt" << std::endl;
        close(server_fd);
        return 1;
    }
    fcntl(server_fd, F_SETFL, O_NONBLOCK);
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(std::stoi(std::string(port)));

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
    socket_fds.push_back({server_fd, POLLIN, 0});
    return (0);
}
