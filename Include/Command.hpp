/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:32:10 by macbook           #+#    #+#             */
/*   Updated: 2025/07/24 13:38:59 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <vector>
#include <optional>
#include <cstddef>
#include <iostream>

struct paramstruct
{
    std::string name;
	std::string value;
};

class Command {
public:
    Command() = default;
    Command(std::string rawCommand, std::vector<struct paramstruct> arguments, int fd);
	Command& operator=(const Command&) = default;
    const std::vector<struct paramstruct>& getParams() const;
    size_t paramCount() const;

    void setCommand(std::string newcommand);
    const std::string& getCommand(void) const;

private:
    std::string         prefix;
    std::string         command;
    std::vector<struct paramstruct>  params;
    int                 user_fd;
};
