/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServerCommandExecutor.cpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:11:44 by psenko            #+#    #+#             */
/*   Updated: 2025/10/02 17:03:31 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/IrcServer.hpp"

void IrcServer::commandExecutor(Command &command) {
  int nn = 0;
  std::cout << "Command entered is" << command.getCommand() << std::endl;

  for (nn = 0; nn < (COMMANDS_COUNT - 1); nn++) {
    if (irccommands[nn] == command.getCommand())
      break;
  }
  (this->*executors[nn])(command);
}
