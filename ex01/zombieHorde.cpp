/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 02:00:34 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/05/11 02:05:47 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie *zombieHorde(int N, std::string name)
{
	Zombie *horde;
	int i;

	if (N <= 0)
		return (NULL);
	horde = new Zombie[N];
	i = 0;
	while (i < N)
	{
		horde[i].setName(name);
		i++;
	}
	return (horde);
}
