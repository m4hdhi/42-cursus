/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 13:04:50 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/07/05 16:12:05 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

WrongCat::WrongCat(void) : WrongAnimal("WrongCat")
{
	std::cout << "Default constructor of " << this->type << std::endl;
}

WrongCat::WrongCat(const WrongCat&) : WrongAnimal("WrongCat")
{
	std::cout << "Copy-Constructor of " << this->type << std::endl;
}

WrongCat::~WrongCat(void)
{
	std::cout << this->type << " has been destroyed" << std::endl;
}

WrongCat&	WrongCat::operator=(const WrongCat& other)
{
	if (this != &other)
		this->type = other.type;
	return (*this);
}

void	WrongCat::makeSound(void) const
{
	std::cout << "* WrongCat Meow *" << std::endl;
}
