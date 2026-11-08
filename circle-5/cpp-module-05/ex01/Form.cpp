/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 04:15:15 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/10/11 04:15:16 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form() : _name("default"), _isSigned(false), _signGrade(GRADE_MAX), _executeGrade(GRADE_MAX)
{
    std::cout << "Default constructor called - (Form)" << std::endl;
}

Form::Form(std::string const &name, int gradeToSign, int gradeToExecute)
    : _name(name), _isSigned(false), _signGrade(gradeToSign), _executeGrade(gradeToExecute)
{
    std::cout << "Parametric constructor called - (Form)" << std::endl;
    if (gradeToSign < GRADE_MIN || gradeToExecute < GRADE_MIN)
        throw Form::GradeTooHighException();
    if (gradeToSign > GRADE_MAX || gradeToExecute > GRADE_MAX)
        throw Form::GradeTooLowException();
}

Form::Form(Form const &other)
    : _name(other._name), _isSigned(other._isSigned), _signGrade(other._signGrade), _executeGrade(other._executeGrade)
{
    std::cout << "Copy constructor called - (Form)" << std::endl;
}

Form &Form::operator=(Form const &other)
{
    std::cout << "Assignation operator called - (Form)" << std::endl;
    // Name and grades are const; only the signed status can be copied.
    if (this != &other)
        _isSigned = other._isSigned;
    return *this;
}

Form::~Form()
{
    std::cout << "Destructor called - (Form)" << std::endl;
}

std::string const &Form::getName() const
{
    return _name;
}

bool Form::getSigned() const
{
    return _isSigned;
}

int Form::getGradeToSign() const
{
    return _signGrade;
}

int Form::getGradeToExecute() const
{
    return _executeGrade;
}

void Form::beSigned(Bureaucrat const &bureaucrat)
{
    if (bureaucrat.getGrade() > _signGrade)
        throw Form::GradeTooLowException();
    _isSigned = true;
}

const char *Form::GradeTooHighException::what() const throw()
{
    return "grade is too high";
}

const char *Form::GradeTooLowException::what() const throw()
{
    return "grade is too low";
}

std::ostream &operator<<(std::ostream &out, Form const &form)
{
    out << "Form " << form.getName()
        << " [signed: " << (form.getSigned() ? "yes" : "no")
        << ", grade to sign: " << form.getGradeToSign()
        << ", grade to execute: " << form.getGradeToExecute() << "]";
    return out;
}
