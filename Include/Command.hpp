/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:32:10 by macbook           #+#    #+#             */
/*   Updated: 2025/07/24 12:46:26 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <vector>
#include <optional>
#include <cstddef>
#include <iostream>
#include "Param.hpp"

class Command {
public:
    Command() = default;
    Command(std::string rawCommand, std::vector<Param> arguments, int fd);
	Command& operator=(const Command&) = default;
    const std::vector<Param>& getParams() const;
    size_t paramCount() const;

    void setCommand(std::string newcommand);
    const std::string& getCommand(void) const;

private:
    std::string         command;
    std::vector<Param>  params;
    int                 user_fd;
};
