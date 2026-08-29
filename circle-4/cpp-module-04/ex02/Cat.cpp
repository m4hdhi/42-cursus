/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 13:07:09 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/07/05 16:12:45 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat(void)
{
		this->type = "Cat";
        std::cout << "Default constructor of " << this->type << std::endl;
		this->brain = new Brain;
}

Cat::Cat(const Cat& other)
{
		this->type = other.type;
        std::cout << "Copy-Constructor of " << this->type << std::endl;
		this->brain = new Brain(*other.brain);
}

Cat::~Cat(void)
{
        std::cout << this->type << " has been destroyed" << std::endl;
		delete this->brain;
}

Cat&		Cat::operator=(const Cat& other)
{
	this->type = other.type;
	*(this->brain) = *(other.brain);

	return (*this);
}

Animal&		Cat::operator=(const Animal& other)
{
	const Cat	*pOther;

	pOther= dynamic_cast<const Cat *>(&other);
	if (pOther)
	{
		this->type = pOther->type;
		*this->brain = *pOther->brain;
	}

	return (*this);
}

void    Cat::makeSound(void) const
{
        std::cout << "* Meow! *" << std::endl;
}

Brain*	Cat::getBrain(void) const
{
	return (this->brain);
}
