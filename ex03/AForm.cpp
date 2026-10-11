/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 04:16:40 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/10/11 04:16:41 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm() : _name("default"), _isSigned(false), _signGrade(GRADE_MAX), _executeGrade(GRADE_MAX)
{
    std::cout << "Default constructor called - (AForm)" << std::endl;
}

AForm::AForm(std::string const &name, int gradeToSign, int gradeToExecute)
    : _name(name), _isSigned(false), _signGrade(gradeToSign), _executeGrade(gradeToExecute)
{
    std::cout << "Parametric constructor called - (AForm)" << std::endl;
    if (gradeToSign < GRADE_MIN || gradeToExecute < GRADE_MIN)
        throw AForm::GradeTooHighException();
    if (gradeToSign > GRADE_MAX || gradeToExecute > GRADE_MAX)
        throw AForm::GradeTooLowException();
}

AForm::AForm(AForm const &other)
    : _name(other._name), _isSigned(other._isSigned), _signGrade(other._signGrade), _executeGrade(other._executeGrade)
{
    std::cout << "Copy constructor called - (AForm)" << std::endl;
}

AForm &AForm::operator=(AForm const &other)
{
    std::cout << "Assignation operator called - (AForm)" << std::endl;
    // Name and grades are const; only the signed status can be copied.
    if (this != &other)
        _isSigned = other._isSigned;
    return *this;
}

AForm::~AForm()
{
    std::cout << "Destructor called - (AForm)" << std::endl;
}

std::string const &AForm::getName() const
{
    return _name;
}

bool AForm::getSigned() const
{
    return _isSigned;
}

int AForm::getGradeToSign() const
{
    return _signGrade;
}

int AForm::getGradeToExecute() const
{
    return _executeGrade;
}

void AForm::beSigned(Bureaucrat const &bureaucrat)
{
    if (bureaucrat.getGrade() > _signGrade)
        throw AForm::GradeTooLowException();
    _isSigned = true;
}

void AForm::execute(Bureaucrat const &executor) const
{
    if (!_isSigned)
        throw AForm::FormNotSignedException();
    if (executor.getGrade() > _executeGrade)
        throw AForm::GradeTooLowException();
    executeAction();
}

const char *AForm::GradeTooHighException::what() const throw()
{
    return "grade is too high";
}

const char *AForm::GradeTooLowException::what() const throw()
{
    return "grade is too low";
}

const char *AForm::FormNotSignedException::what() const throw()
{
    return "form is not signed";
}

std::ostream &operator<<(std::ostream &out, AForm const &form)
{
    out << "Form " << form.getName()
        << " [signed: " << (form.getSigned() ? "yes" : "no")
        << ", grade to sign: " << form.getGradeToSign()
        << ", grade to execute: " << form.getGradeToExecute() << "]";
    return out;
}
