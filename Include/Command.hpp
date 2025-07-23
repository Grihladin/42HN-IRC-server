/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:32:10 by macbook           #+#    #+#             */
/*   Updated: 2025/07/23 16:54:00 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <vector>
#include <optional>
#include <cstddef>
#include <iostream>

class Command {
public:
    Command(std::string rawCommand, std::vector<std::string> arguments);
	Command& operator=(const Command&) = default;
    const std::string& getCommand() const;
    const std::vector<std::string>& getArgs() const;
    size_t argCount() const;

private:
    std::string command;
    std::vector<std::string> args;
};