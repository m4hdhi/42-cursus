/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 04:16:27 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/10/11 04:16:28 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm() : AForm("ShrubberyCreationForm", 145, 137), _target("default")
{
    std::cout << "Default constructor called - (ShrubberyCreationForm)" << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(std::string const &target) : AForm("ShrubberyCreationForm", 145, 137), _target(target)
{
    std::cout << "Parametric constructor called - (ShrubberyCreationForm)" << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const &other) : AForm(other), _target(other._target)
{
    std::cout << "Copy constructor called - (ShrubberyCreationForm)" << std::endl;
}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(ShrubberyCreationForm const &other)
{
    std::cout << "Assignation operator called - (ShrubberyCreationForm)" << std::endl;
    if (this != &other)
    {
        AForm::operator=(other);
        _target = other._target;
    }
    return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
    std::cout << "Destructor called - (ShrubberyCreationForm)" << std::endl;
}

std::string const &ShrubberyCreationForm::getTarget() const
{
    return _target;
}

void ShrubberyCreationForm::executeAction() const
{
    std::string filename = _target + "_shrubbery";
    std::ofstream outputFile(filename.c_str(), std::ofstream::trunc);

    if (!outputFile.is_open())
        throw ShrubberyCreationForm::FileOpenException();

    outputFile << "       _-_" << std::endl;
    outputFile << "    /~~   ~~\\" << std::endl;
    outputFile << " /~~         ~~\\" << std::endl;
    outputFile << "{               }" << std::endl;
    outputFile << " \\  _-     -_  /" << std::endl;
    outputFile << "   ~  \\ //  ~" << std::endl;
    outputFile << "_- -   | | _- _" << std::endl;
    outputFile << "  _ -  | |   -_" << std::endl;
    outputFile << "      // \\\\" << std::endl;
    outputFile.close();
}

const char *ShrubberyCreationForm::FileOpenException::what() const throw()
{
    return "could not create the shrubbery file";
}
