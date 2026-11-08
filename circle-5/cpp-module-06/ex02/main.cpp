/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 03:28:20 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/10/25 03:28:22 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base *generate(void) {
    switch (std::rand() % 3) {
        case 0:
            return new A;
        case 1:
            return new B;
        default:
            return new C;
    }
}

void identify(Base* p) {
    if (dynamic_cast<A *>(p))
        std::cout << "A" << std::endl;
    else if (dynamic_cast<B *>(p))
        std::cout << "B" << std::endl;
    else if (dynamic_cast<C *>(p))
        std::cout << "C" << std::endl;
    else
        std::cout << "Unknown type" << std::endl;
}

void identify(Base& p) {
    try {
        (void)dynamic_cast<A &>(p);
        std::cout << "A" << std::endl;
        return;
    } catch (...) {}
    try {
        (void)dynamic_cast<B &>(p);
        std::cout << "B" << std::endl;
        return;
    } catch (...) {}
    try {
        (void)dynamic_cast<C &>(p);
        std::cout << "C" << std::endl;
        return;
    } catch (...) {}
    std::cout << "Unknown type" << std::endl;
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(NULL)));

    for (int i = 0; i < 5; i++) {
        Base *b = generate();
        std::cout << "pointer:   ";
        identify(b);
        std::cout << "reference: ";
        identify(*b);
        std::cout << std::endl;
        delete b;
    }

    Base *nothing = NULL;
    std::cout << "NULL pointer: ";
    identify(nothing);

    Base base;
    std::cout << "plain Base:   ";
    identify(base);
    return 0;
}
