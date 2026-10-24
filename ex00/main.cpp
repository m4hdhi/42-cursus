/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 03:26:53 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/10/25 03:32:57 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "ScalarConverter.hpp"

int main(int ac, char* av[])
{
    if (ac != 2) {
        std::cout << "Usage: ./convert <literal>" << std::endl;
        return 1;
    }
    ScalarConverter::convert(av[1]);
    return 0;
}
