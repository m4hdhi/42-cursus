/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 02:00:15 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/05/11 02:05:35 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main(void)
{
	Zombie *horde;
	int n;
	int i;

	n = 5;
	horde = zombieHorde(n, "Horde zombie");
	if (!horde)
		return (1);
	i = 0;
	while (i < n)
	{
		horde[i].announce();
		i++;
	}
	delete[] horde;
	return (0);
}
