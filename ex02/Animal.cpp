/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 13:06:40 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/07/05 16:12:35 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::~Animal(void)
{
	std::cout << "Destructor of Animal" << std::endl;
}

const std::string&	Animal::getType(void) const
{
	return (this->type);
}
