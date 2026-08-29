/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:49:21 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/06/12 18:35:17 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCAVTRAP_HPP
# define SCAVTRAP_HPP

#include "ClapTrap.hpp"

class ScavTrap : public ClapTrap {
	public:
		ScavTrap(const std::string& name);
		ScavTrap(const ScavTrap& other);
		ScavTrap(void);
		~ScavTrap(void);

		ScavTrap&	operator=(const ScavTrap& other);
		void	attack(const std::string& target);
		void	guardGate(void) const;
};

#endif
