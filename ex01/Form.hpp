/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 04:15:19 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/10/11 04:15:20 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
# define FORM_HPP

# include <iostream>
# include <string>
# include <exception>

class Bureaucrat;

class Form
{
private:
    std::string const _name;
    bool _isSigned;
    int const _signGrade;
    int const _executeGrade;

public:
    Form();
    Form(std::string const &name, int gradeToSign, int gradeToExecute);
    Form(Form const &other);
    Form &operator=(Form const &other);
    ~Form();

    std::string const &getName() const;
    bool getSigned() const;
    int getGradeToSign() const;
    int getGradeToExecute() const;

    void beSigned(Bureaucrat const &bureaucrat);

    class GradeTooHighException : public std::exception
    {
        public:
            virtual const char *what() const throw();
    };
    class GradeTooLowException : public std::exception
    {
        public:
            virtual const char *what() const throw();
    };
};

std::ostream &operator<<(std::ostream &out, Form const &form);

#endif
