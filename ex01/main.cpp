/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 03:27:27 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/10/25 03:27:28 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Serializer.hpp"

int main()
{
    Data data;
    data.id = 42;
    data.name = "forty-two";

    uintptr_t raw = Serializer::serialize(&data);
    Data *ptr = Serializer::deserialize(raw);

    std::cout << "Original pointer:     " << &data << std::endl;
    std::cout << "Serialized value:     " << raw << std::endl;
    std::cout << "Deserialized pointer: " << ptr << std::endl;

    if (ptr == &data)
        std::cout << "OK: deserialized pointer equals the original" << std::endl;
    else
        std::cout << "KO: pointers differ" << std::endl;

    std::cout << "ptr->id:   " << ptr->id << std::endl;
    std::cout << "ptr->name: " << ptr->name << std::endl;
    return 0;
}
