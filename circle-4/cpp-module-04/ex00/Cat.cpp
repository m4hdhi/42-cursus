/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 13:03:54 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/07/05 16:11:47 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat(void) : Animal("Cat")
{
        std::cout << "Default constructor of " << this->type << std::endl;
}

Cat::Cat(const Cat&) : Animal("Cat")
{
        std::cout << "Copy-Constructor of " << this->type << std::endl;
}

Cat::~Cat(void)
{
        std::cout << this->type << " has been destroyed" << std::endl;
}

Cat&    Cat::operator=(const Cat& other)
{
        if (this != &other)
                this->type = other.type;
        return (*this);
}

void    Cat::makeSound(void) const
{
        std::cout << "* Meow! *" << std::endl;
}

