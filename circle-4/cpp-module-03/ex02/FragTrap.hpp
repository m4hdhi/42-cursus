/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:48:58 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/06/12 18:35:05 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAGTRAP_HPP
# define FRAGTRAP_HPP

#include "ClapTrap.hpp"

class FragTrap : public ClapTrap {
	public:
		FragTrap(const std::string& name);
		FragTrap(const FragTrap& other);
		FragTrap(void);
		~FragTrap(void);

		FragTrap&	operator=(const FragTrap& other);
		void	highFivesGuys(void) const;
};

#endif
