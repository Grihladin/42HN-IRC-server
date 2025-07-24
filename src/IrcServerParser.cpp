/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServerParser.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 10:56:53 by psenko            #+#    #+#             */
/*   Updated: 2025/07/24 11:44:03 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/IrcServer.hpp"

const Command IrcServer::commandParser(std::string rawdata)
{
    Command     newcommand;
    std::cout << rawdata << std::endl;
    newcommand.setCommand("USER");
    return (newcommand);
}