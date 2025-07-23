/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 13:26:40 by psenko            #+#    #+#             */
/*   Updated: 2025/07/23 11:54:51 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcServer.hpp"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cerr << "Wrong count of parameters. I need at least a port and a password." << std::endl;
        return 1;
    }

    try
    {
        IrcServer ircserver(argv[1], argv[2]);
        ircserver.listenSocket();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    
    return 0;
}
