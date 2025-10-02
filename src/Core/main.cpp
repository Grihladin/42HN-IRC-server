/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 13:26:40 by psenko            #+#    #+#             */
/*   Updated: 2025/10/02 17:03:41 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Command.hpp"
#include "../../inc/IrcServer.hpp"
#include <csignal>

volatile sig_atomic_t sigintstatus;

void signal_handler(int signal) { sigintstatus = signal; }

int main(int argc, char **argv) {
  signal(SIGINT, signal_handler);
  if (argc != 3) {
    std::cerr
        << "Wrong count of parameters. I need at least a port and a password."
        << std::endl;
    return 1;
  }

  try {
    IrcServer ircserver(argv[1], argv[2]);
    while (!sigintstatus)
      ircserver.listenSocket();
    std::cout << "Stopping the server" << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return (1);
  }
  return 0;
}
