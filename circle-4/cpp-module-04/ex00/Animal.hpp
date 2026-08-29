/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 13:03:46 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/07/05 16:11:44 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
# define ANIMAL_HPP

#include <iostream>
#include <string>

class Animal {
	protected:
		std::string	type;
		Animal(const std::string& type);
	public:
		Animal(void);
		Animal(const Animal& other);
		virtual ~Animal(void);

		Animal&				operator=(const Animal& other);
		const std::string&	getType(void) const;
		virtual void		makeSound(void) const;
};

#endif
