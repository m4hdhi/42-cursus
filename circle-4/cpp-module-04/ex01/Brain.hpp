/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 13:05:46 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/07/05 16:12:21 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_HPP
# define BRAIN_HPP

#include <iostream>
#include <string>

class Brain {
	private:
		std::string		ideas[100];
		unsigned int	size;
	public:
		Brain(void);
		Brain(const Brain& other);
		~Brain(void);

		Brain&				operator=(const Brain& other);
		void				addIdea(std::string idea);
		const std::string&	getIdea(unsigned int index) const;
};

#endif
