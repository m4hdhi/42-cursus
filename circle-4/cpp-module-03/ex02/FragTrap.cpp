/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:48:53 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/06/12 18:35:03 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap(void) : ClapTrap()
{
	this->hitPoints = 100;
	this->energyPoints = 100;
	this->attackDamage = 30;
	std::cout << "FragTrap default constructor has been called!" << std::endl;
}

FragTrap::FragTrap(const std::string& name) : ClapTrap(name)
{
	this->hitPoints = 100;
	this->energyPoints = 100;
	this->attackDamage = 30;
	std::cout << "<FragTrap " << this->name << "> Status: Created" << std::endl;
}

FragTrap::FragTrap(const FragTrap& other) : ClapTrap(other)
{
	std::cout << "<FragTrap copy-constructor has been called!> Status: Cloned" << std::endl;
}

FragTrap::~FragTrap(void)
{
	std::cout << "<FragTrap " << this->name << "> Status: Dead" << std::endl;
}

FragTrap&	FragTrap::operator=(const FragTrap& other)
{
	ClapTrap::operator=(other);
	return (*this);
}

void	FragTrap::highFivesGuys(void) const
{
	std::cout << "<FragTrap " << this->name << "> High Five Guys! Status: Friendly" << std::endl;
}
