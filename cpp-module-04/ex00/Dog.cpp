/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 13:04:06 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/07/05 16:11:52 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog(void) : Animal("Dog")
{
	std::cout << "Default constructor of " << this->type << std::endl;
}

Dog::Dog(const Dog&) : Animal("Dog")
{
	std::cout << "Copy-Constructor of " << this->type << std::endl;
}

Dog::~Dog(void)
{
	std::cout << this->type << " has been destroyed" << std::endl;
}

Dog&	Dog::operator=(const Dog& other)
{
	if (this != &other)
		this->type = other.type;
	return (*this);
}

void	Dog::makeSound(void) const
{
	std::cout << "* Barking! *" << std::endl;
}
