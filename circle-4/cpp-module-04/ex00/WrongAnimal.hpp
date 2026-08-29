/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 13:04:42 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/07/05 16:12:03 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONG_ANIMAL_HPP
# define WRONG_ANIMAL_HPP

#include <iostream>
#include <string>

class WrongAnimal {
	protected:
		std::string    type;
		WrongAnimal(const std::string& type);
	public:
		WrongAnimal(void);
		WrongAnimal(const WrongAnimal& other);
		virtual ~WrongAnimal(void);

		WrongAnimal&		operator=(const WrongAnimal& other);
		const std::string&	getType(void) const;
		void		makeSound(void) const;
};

#endif
