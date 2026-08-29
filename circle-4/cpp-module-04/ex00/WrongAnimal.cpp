/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 13:04:30 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/07/05 16:12:01 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal(void)
{
	std::cout << "Default Constructor of WrongAnimal" << std::endl;
}

WrongAnimal::WrongAnimal(const std::string& type)
{
	std::cout << "Type constructor of WrongAnimal" << std::endl;
	this->type = type;
}

WrongAnimal::WrongAnimal(const WrongAnimal& other)
{
	std::cout << "Copy-Constructor of WrongAnimal" << std::endl;
	*this = other; 
}

WrongAnimal::~WrongAnimal(void)
{
	std::cout << "Destructor of WrongAnimal" << std::endl;
}

WrongAnimal&				WrongAnimal::operator=(const WrongAnimal& other)
{
	this->type = other.getType();

	return (*this);
}

const std::string&	WrongAnimal::getType(void) const
{
	return (this->type);
}

void				WrongAnimal::makeSound(void) const
{
	std::cout << "* WrongAnimal Sound!!! *" << std::endl;
}
                                                        
