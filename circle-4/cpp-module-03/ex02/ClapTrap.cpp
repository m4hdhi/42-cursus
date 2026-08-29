/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:48:42 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/06/12 18:34:56 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

/* Constructors and the Destructor */
ClapTrap::ClapTrap(void)
{
	std::cout << "ClapTrap default constructor has been called!" << std::endl;
	this->hitPoints = 100;
	this->energyPoints = 100;
	this->attackDamage = 30;
}

ClapTrap::ClapTrap(const ClapTrap& other) 
{ 
	std::cout << "<ClapTrap copy-constructor has been called!> Status: Cloned" << std::endl;
	*this = other;

} 

ClapTrap::ClapTrap(std::string name)
{
	std::cout << "<ClapTrap " << name << "> " << "Status: Created" << std::endl;
	this->name = name;
	this->hitPoints = 10;
	this->energyPoints = 10;
	this->attackDamage = 0;
}

ClapTrap::~ClapTrap(void)
{
	std::cout << "<ClapTrap " << this->name << "> " << "Status: Dead" << std::endl;
}

/* Assignation operator overload */
ClapTrap&			ClapTrap::operator=(const ClapTrap& other)
{
	this->setName(other.getName());
	this->setHitPoints(other.getHitPoints());
	this->setEnergyPoints(other.getEnergyPoints());
	this->setAttackDamage(other.getAttackDamage());

	return (*this);
}

/* Getters and Setters */
const std::string&	ClapTrap::getName(void) const
{
	return (this->name);
}

unsigned int		ClapTrap::getHitPoints(void) const
{
	return (this->hitPoints);
}

unsigned int		ClapTrap::getEnergyPoints(void) const
{
	return (this->energyPoints);
}

unsigned int		ClapTrap::getAttackDamage(void) const
{
	return (this->attackDamage);
}

void				ClapTrap::setName(const std::string& name)
{
	this->name = name;
}

void				ClapTrap::setHitPoints(unsigned int hitPoints)
{
	this->hitPoints = hitPoints;
}

void				ClapTrap::setEnergyPoints(unsigned int energyPoints)
{
	this->energyPoints = energyPoints;
}

void				ClapTrap::setAttackDamage(unsigned int damage)
{
	this->attackDamage = damage;
}

/* Action functions */
void				ClapTrap::attack(const std::string& target)
{
	if (this->hitPoints == 0 || this->energyPoints == 0)
	{
		std::cout << "<ClapTrap " << this->name << " can't attack> ";
		std::cout << "Hitpoints: " << this->hitPoints << " Energy: " << this->energyPoints << " Status: Exhausted" << std::endl;
		return ;
	}
	this->energyPoints -= 1;
	std::cout << "<ClapTrap " << this->name << " attacks " << target;
	std::cout << ", causing " << this->attackDamage << " points of damage!> ";
	std::cout << "Energy: " << this->energyPoints << " Status: Attacked" << std::endl;
}

void				ClapTrap::takeDamage(unsigned int amount)
{
	if (amount > this->hitPoints)
		this->hitPoints = 0;
	else
		this->hitPoints -= amount;
	std::cout << "<ClapTrap " << this->name << " got " << amount << " points of damage!>";
	std::cout << " Hitpoints: " << this->hitPoints << " Status: Damaged" << std::endl;
}

void				ClapTrap::beRepaired(unsigned int amount)
{
	if (this->hitPoints == 0 || this->energyPoints == 0)
	{
		std::cout << "<ClapTrap " << this->name << " can't repair> ";
		std::cout << "Hitpoints: " << this->hitPoints << " Energy: " << this->energyPoints << " Status: Exhausted" << std::endl;
		return ;
	}
	this->energyPoints -= 1;
	this->hitPoints += amount;
	std::cout << "<ClapTrap " << this->name << " got repaired by " << amount << " points!>";
	std::cout << " Hitpoints: " << this->hitPoints << " Energy: " << this->energyPoints << " Status: Repaired" << std::endl;
}
