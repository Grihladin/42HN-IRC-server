/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Param.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:02:57 by psenko            #+#    #+#             */
/*   Updated: 2025/07/24 11:10:28 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <cstddef>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

class Param
{
  public:
	Param() = default;
	// Setters
	void setName(const std::string &paramname);
	void setValue(const std::string &newvalue);
	// Getters
	std::string getName() const;
	std::string getValue() const;

  private:
	std::string name;
	std::string value;
};
