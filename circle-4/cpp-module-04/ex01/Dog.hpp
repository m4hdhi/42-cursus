/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 13:06:09 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/07/05 16:12:30 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
# define DOG_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal {
	private:
		Brain	*brain;
	public:
		Dog(void);
		Dog(const Dog& other);
		~Dog();

		Dog&	operator=(const Dog& other);
		Animal&	operator=(const Animal& other);
		void	makeSound(void) const;
		Brain	*getBrain(void) const;
};

#endif
