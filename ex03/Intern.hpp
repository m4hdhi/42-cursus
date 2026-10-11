/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 04:17:05 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/10/11 04:17:06 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_HPP
# define INTERN_HPP

# include <string>

class AForm;

class Intern
{
private:
    typedef AForm *(Intern::*t_creator)(std::string const &) const;

    AForm *createShrubberyForm(std::string const &target) const;
    AForm *createRobotomyForm(std::string const &target) const;
    AForm *createPresidentialPardonForm(std::string const &target) const;

public:
    Intern();
    Intern(Intern const &other);
    Intern &operator=(Intern const &other);
    ~Intern();

    AForm *makeForm(std::string const &formName, std::string const &target) const;
};

#endif
