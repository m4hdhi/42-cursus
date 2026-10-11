/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 04:17:01 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/10/11 04:17:02 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "AForm.hpp"
#include <iostream>

Intern::Intern()
{
    std::cout << "Default constructor called - (Intern)" << std::endl;
}

Intern::Intern(Intern const &other)
{
    std::cout << "Copy constructor called - (Intern)" << std::endl;
    *this = other;
}

Intern &Intern::operator=(Intern const &other)
{
    std::cout << "Assignation operator called - (Intern)" << std::endl;
    (void)other;
    return *this;
}

Intern::~Intern()
{
    std::cout << "Destructor called - (Intern)" << std::endl;
}

AForm *Intern::createShrubberyForm(std::string const &target) const
{
    return new ShrubberyCreationForm(target);
}

AForm *Intern::createRobotomyForm(std::string const &target) const
{
    return new RobotomyRequestForm(target);
}

AForm *Intern::createPresidentialPardonForm(std::string const &target) const
{
    return new PresidentialPardonForm(target);
}

AForm *Intern::makeForm(std::string const &formName, std::string const &target) const
{
    static const std::string names[] = {
        "shrubbery creation",
        "robotomy request",
        "presidential pardon"
    };
    static const t_creator creators[] = {
        &Intern::createShrubberyForm,
        &Intern::createRobotomyForm,
        &Intern::createPresidentialPardonForm
    };
    const size_t formCount = sizeof(names) / sizeof(names[0]);

    for (size_t i = 0; i < formCount; ++i)
    {
        if (formName == names[i])
        {
            AForm *form = (this->*creators[i])(target);
            std::cout << "Intern creates " << form->getName() << std::endl;
            return form;
        }
    }
    std::cout << "Intern couldn't create \"" << formName
              << "\": no such form (expected \"shrubbery creation\", "
              << "\"robotomy request\" or \"presidential pardon\")" << std::endl;
    return NULL;
}
