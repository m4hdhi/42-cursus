/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 04:17:30 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/10/11 04:17:31 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"
#include <cstdlib>
#include <ctime>

RobotomyRequestForm::RobotomyRequestForm() : AForm("RobotomyRequestForm", 72, 45), _target("default")
{
    std::cout << "Default constructor called - (RobotomyRequestForm)" << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(std::string const &target) : AForm("RobotomyRequestForm", 72, 45), _target(target)
{
    std::cout << "Parametric constructor called - (RobotomyRequestForm)" << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(RobotomyRequestForm const &other) : AForm(other), _target(other._target)
{
    std::cout << "Copy constructor called - (RobotomyRequestForm)" << std::endl;
}

RobotomyRequestForm &RobotomyRequestForm::operator=(RobotomyRequestForm const &other)
{
    std::cout << "Assignation operator called - (RobotomyRequestForm)" << std::endl;
    if (this != &other)
    {
        AForm::operator=(other);
        _target = other._target;
    }
    return *this;
}

RobotomyRequestForm::~RobotomyRequestForm()
{
    std::cout << "Destructor called - (RobotomyRequestForm)" << std::endl;
}

std::string const &RobotomyRequestForm::getTarget() const
{
    return _target;
}

void RobotomyRequestForm::executeAction() const
{
    static bool seeded = false;

    if (!seeded)
    {
        std::srand(std::time(NULL));
        seeded = true;
    }
    std::cout << "* BZZZZZRRRRR... drilling noises... BZZZZRRRR *" << std::endl;
    if (std::rand() % 2)
        std::cout << _target << " has been robotomized successfully." << std::endl;
    else
        std::cout << "The robotomy on " << _target << " failed." << std::endl;
}
