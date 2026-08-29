/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 13:07:19 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/07/05 16:12:52 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog(void)
{
	this->type = "Dog";
	std::cout << "Default constructor of " << this->type << std::endl;
	this->brain = new Brain;
}

Dog::Dog(const Dog& other)
{
	this->type = other.type;
	std::cout << "Copy-Constructor of " << this->type << std::endl;
	this->brain = new Brain(*other.brain);
}

Dog::~Dog(void)
{
	std::cout << this->type << " has been destroyed" << std::endl;
	delete this->brain;
}

Dog&		Dog::operator=(const Dog& other)
{
	this->type = other.type;
	*(this->brain) = *(other.brain);

	return (*this);
}

Animal&		Dog::operator=(const Animal& other)
{
	const Dog	*pOther; 

	pOther = dynamic_cast<const Dog*>(&other);
	if(pOther)
	{
		this->type = pOther->type;
		*this->brain = *pOther->brain;
	}

	return (*this);
}

void	Dog::makeSound(void) const
{
	std::cout << "* Barking! *" << std::endl;
}

Brain*	Dog::getBrain(void) const
{
	return (this->brain);
}
