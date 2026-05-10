/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 02:02:03 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/05/11 02:06:33 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

Harl::Harl(void)
{
}

Harl::~Harl(void)
{
}

void Harl::debug(void)
{
	std::cout << "[ DEBUG ]" << std::endl;
	std::cout << "I love having extra bacon for my "
		<< "7XL-double-cheese-triple-pickle-special-ketchup burger. "
		<< "I really do!" << std::endl;
}

void Harl::info(void)
{
	std::cout << "[ INFO ]" << std::endl;
	std::cout << "I cannot believe adding extra bacon costs more money. "
		<< "You didn't put enough bacon in my burger! "
		<< "If you did, I wouldn't be asking for more!" << std::endl;
}

void Harl::warning(void)
{
	std::cout << "[ WARNING ]" << std::endl;
	std::cout << "I think I deserve to have some extra bacon for free. "
		<< "I've been coming for years, whereas you started working "
		<< "here just last month." << std::endl;
}

void Harl::error(void)
{
	std::cout << "[ ERROR ]" << std::endl;
	std::cout << "This is unacceptable! I want to speak to the manager now."
		<< std::endl;
}

int Harl::getLevel(std::string level) const
{
	if (level == "DEBUG")
		return (0);
	if (level == "INFO")
		return (1);
	if (level == "WARNING")
		return (2);
	if (level == "ERROR")
		return (3);
	return (-1);
}

void Harl::complain(std::string level)
{
	void (Harl::*functions[4])(void) = {
		&Harl::debug,
		&Harl::info,
		&Harl::warning,
		&Harl::error
	};
	int i;

	switch (getLevel(level))
	{
		case 0:
			i = 0;
			break;
		case 1:
			i = 1;
			break;
		case 2:
			i = 2;
			break;
		case 3:
			i = 3;
			break;
		default:
			std::cout << "[ Probably complaining about insignificant problems ]"
				<< std::endl;
			return;
	}
	while (i < 4)
	{
		(this->*functions[i])();
		if (i != 3)
			std::cout << std::endl;
		i++;
	}
}
