/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 04:15:23 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/10/11 04:15:24 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"

int main()
{
    std::cout << "\n--- Signing: grade high enough / too low / exactly equal ---" << std::endl;
    try
    {
        Bureaucrat boss("Boss", 1);
        Bureaucrat intern("Intern", 150);
        Bureaucrat clerk("Clerk", 50);
        Form taxes("Taxes", 50, 25);
        Form permit("Permit", 10, 5);

        std::cout << taxes << std::endl;
        std::cout << permit << std::endl;

        intern.signForm(taxes);
        clerk.signForm(taxes);
        clerk.signForm(permit);
        boss.signForm(permit);

        std::cout << taxes << std::endl;
        std::cout << permit << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << "\n--- Form with sign grade 0 ---" << std::endl;
    try
    {
        Form invalid("Invalid", 0, 10);
        std::cout << invalid << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << "\n--- Form with execute grade 151 ---" << std::endl;
    try
    {
        Form invalid("Invalid", 10, 151);
        std::cout << invalid << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << "\n--- beSigned() throws directly when grade is too low ---" << std::endl;
    try
    {
        Bureaucrat low("Low", 100);
        Form form("Contract", 20, 20);
        form.beSigned(low);
        std::cout << "This line should not be printed" << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
    return 0;
}
