/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 04:16:02 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/10/11 04:16:03 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main()
{
    try
    {
        Bureaucrat president("President", 1);
        Bureaucrat manager("Manager", 45);
        Bureaucrat clerk("Clerk", 140);

        ShrubberyCreationForm shrubbery("home");
        RobotomyRequestForm robotomy("Bender");
        PresidentialPardonForm pardon("Arthur Dent");

        std::cout << "\n--- Forms ---" << std::endl;
        std::cout << shrubbery << std::endl;
        std::cout << robotomy << std::endl;
        std::cout << pardon << std::endl;

        std::cout << "\n--- Executing unsigned forms ---" << std::endl;
        president.executeForm(shrubbery);
        president.executeForm(robotomy);
        president.executeForm(pardon);

        std::cout << "\n--- Signing ---" << std::endl;
        clerk.signForm(shrubbery);
        clerk.signForm(robotomy);
        manager.signForm(robotomy);
        manager.signForm(pardon);
        president.signForm(pardon);

        std::cout << "\n--- Executing with a grade too low ---" << std::endl;
        clerk.executeForm(shrubbery);
        clerk.executeForm(robotomy);
        manager.executeForm(pardon);

        std::cout << "\n--- Executing with a grade high enough ---" << std::endl;
        president.executeForm(shrubbery);
        manager.executeForm(robotomy);
        manager.executeForm(robotomy);
        manager.executeForm(robotomy);
        manager.executeForm(robotomy);
        president.executeForm(pardon);

        std::cout << "\n--- Calling execute() directly on an unsigned form ---" << std::endl;
        PresidentialPardonForm unsignedPardon("Ford Prefect");
        unsignedPardon.execute(president);
        std::cout << "This line should not be printed" << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
    return 0;
}
