/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 13:03:39 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/07/05 16:11:40 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal(void)
{
	std::cout << "Default Constructor of Animal" << std::endl;
}

Animal::Animal(const std::string& type)
{
	std::cout << "Type constructor of Animal" << std::endl;
	this->type = type;
}

Animal::Animal(const Animal& other)
{
	std::cout << "Copy-Constructor of Animal" << std::endl;
	*this = other; 
}

Animal::~Animal(void)
{
	std::cout << "Destructor of Animal" << std::endl;
}

Animal&				Animal::operator=(const Animal& other)
{
	this->type = other.getType();

	return (*this);
}

const std::string&	Animal::getType(void) const
{
	return (this->type);
}

void				Animal::makeSound(void) const
{
	std::cout << "* Animal Sound!!! *" << std::endl;
}
