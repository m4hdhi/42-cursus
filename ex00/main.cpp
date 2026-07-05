/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 13:04:18 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/07/05 16:11:56 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main()
{
	const Animal* meta = new Animal();
	const Animal* j = new Dog();
	const Animal* i = new Cat();

	std::cout << "\nAnimal testing" << std::endl;
	std::cout << std::endl;
	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;

	std::cout << std::endl;
	i->makeSound(); //will output the cat sound!
	j->makeSound();
	meta->makeSound();

	std::cout << std::endl;
	delete meta;
	delete j;
	delete i;

	std::cout << "\nWrong Animal testing\n" << std::endl;
	const WrongAnimal*	wrongAnimal = new WrongAnimal();
	const WrongAnimal*	wrongCatAsAnimal = new WrongCat();

	std::cout << std::endl;
	std::cout << "WrongAnimal (as WrongAnimal*): ";
	wrongAnimal->makeSound();
	// makeSound() is NOT virtual here, so this still calls WrongAnimal::makeSound()
	std::cout << "WrongCat    (as WrongAnimal*): ";
	wrongCatAsAnimal->makeSound();

	// Used as a real WrongCat, we get the WrongCat sound instead
	WrongCat	realWrongCat;
	std::cout << "WrongCat    (as WrongCat):     ";
	realWrongCat.makeSound();

	std::cout << std::endl;
	delete wrongAnimal;
	delete wrongCatAsAnimal;
}
