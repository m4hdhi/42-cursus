/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:48:27 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/06/12 18:34:46 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap(void) : ClapTrap()
{
	this->hitPoints = 100;
	this->energyPoints = 50;
	this->attackDamage = 20;
	std::cout << "ScavTrap default constructor has been called!" << std::endl;
}

ScavTrap::ScavTrap(const std::string& name) : ClapTrap(name)
{
	this->hitPoints = 100;
	this->energyPoints = 50;
	this->attackDamage = 20;
	std::cout << "<ScavTrap " << this->name << "> Status: Created" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap& other) : ClapTrap(other)
{
	std::cout << "<ScavTrap copy-constructor has been called!> Status: Cloned" << std::endl;
}

ScavTrap::~ScavTrap(void)
{
	std::cout << "<ScavTrap " << this->name << "> Status: Dead" << std::endl;
}

ScavTrap&	ScavTrap::operator=(const ScavTrap& other)
{
	ClapTrap::operator=(other);
	return (*this);
}

void	ScavTrap::attack(const std::string& target)
{
	if (this->hitPoints == 0 || this->energyPoints == 0)
	{
		std::cout << "<ScavTrap " << this->name << " can't attack> ";
		std::cout << "Hitpoints: " << this->hitPoints << " Energy: " << this->energyPoints << " Status: Exhausted" << std::endl;
		return ;
	}
	this->energyPoints -= 1;
	std::cout << "<ScavTrap " << this->name << " attacks " << target;
	std::cout << ", causing " << this->attackDamage << " points of damage!> ";
	std::cout << "Energy: " << this->energyPoints << " Status: Attacked" << std::endl;
}

void	ScavTrap::guardGate(void) const
{
	std::cout << "<ScavTrap " << this->name << " is guarding the gates> ";
	std::cout << "Status: Guarding" << std::endl;
}
