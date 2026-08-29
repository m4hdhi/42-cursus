/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 17:43:54 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/06/03 19:09:56 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed {
	private:
		int 				value;
		static const int	fractBits = 8;
	public:
		Fixed(void);
		Fixed(const Fixed& other);
		~Fixed(void);

		Fixed&	operator=(const Fixed& other);
		int 	getRawBits(void) const;
		void	setRawBits(const int raw);
};

#endif
