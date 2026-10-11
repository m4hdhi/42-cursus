/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 04:15:10 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/10/11 04:15:11 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

# include <iostream>
# include <string>
# include <exception>

class Form;

# define GRADE_MIN 1
# define GRADE_MAX 150

class Bureaucrat
{
private:
    std::string const _name;
    int _grade;

public:
    Bureaucrat();
    Bureaucrat(std::string const &name, int grade);
    Bureaucrat(Bureaucrat const &other);
    Bureaucrat &operator=(Bureaucrat const &other);
    ~Bureaucrat();

    std::string const &getName() const;
    int getGrade() const;

    void incrementGrade();
    void decrementGrade();
    void signForm(Form &form) const;

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

std::ostream &operator<<(std::ostream &out, Bureaucrat const &bureaucrat);

#endif
