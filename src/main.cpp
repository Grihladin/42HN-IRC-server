/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 13:26:40 by psenko            #+#    #+#             */
/*   Updated: 2025/07/25 04:38:55 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/IrcServer.hpp"
#include "../Include/Command.hpp"

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

    // std::vector<std::string> args = {"Sasha"};
	// Command cmd("NICK", args);

	// std::cout << "Command: " << cmd.getCommand() << "\n";
	// std::cout << "Arguments count: " << cmd.argCount() << "\n";

	// const auto &arguments = cmd.getArgs();
	// for (const auto &arg : arguments)
	// {
	// 	std::cout << "Arg: " << arg << "\n";
	// }
    // if(cmd.getCommand() == "NICK")
    // {
    //     std::cout << "We have NICK here" << "\n";
    // }
    return 0;
}
