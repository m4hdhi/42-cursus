/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 04:14:51 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/10/11 04:14:52 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int main()
{
    std::cout << "\n--- Valid bureaucrat, increment / decrement ---" << std::endl;
    try
    {
        Bureaucrat bob("Bob", 3);
        std::cout << bob << std::endl;
        bob.incrementGrade();
        std::cout << "After increment: " << bob << std::endl;
        bob.decrementGrade();
        std::cout << "After decrement: " << bob << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << "\n--- Constructor with grade 0 ---" << std::endl;
    try
    {
        Bureaucrat tooHigh("TooHigh", 0);
        std::cout << tooHigh << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << "\n--- Constructor with grade 151 ---" << std::endl;
    try
    {
        Bureaucrat tooLow("TooLow", 151);
        std::cout << tooLow << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << "\n--- Increment past grade 1 ---" << std::endl;
    try
    {
        Bureaucrat top("Top", 1);
        std::cout << top << std::endl;
        top.incrementGrade();
        std::cout << "This line should not be printed" << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << "\n--- Decrement past grade 150 ---" << std::endl;
    try
    {
        Bureaucrat bottom("Bottom", 150);
        std::cout << bottom << std::endl;
        bottom.decrementGrade();
        std::cout << "This line should not be printed" << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << "\n--- Copy constructor and assignment ---" << std::endl;
    try
    {
        Bureaucrat original("Original", 42);
        Bureaucrat copy(original);
        Bureaucrat assigned("Assigned", 100);
        assigned = original;
        std::cout << original << std::endl;
        std::cout << copy << std::endl;
        std::cout << assigned << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
    return 0;
}
