/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 04:16:32 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/10/11 04:16:33 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHRUBBERY_CREATION_FORM_HPP
# define SHRUBBERY_CREATION_FORM_HPP

# include <string>
# include "AForm.hpp"

class ShrubberyCreationForm : public AForm
{
private:
    std::string _target;

protected:
    void executeAction() const;

public:
    ShrubberyCreationForm();
    ShrubberyCreationForm(std::string const &target);
    ShrubberyCreationForm(ShrubberyCreationForm const &other);
    ShrubberyCreationForm &operator=(ShrubberyCreationForm const &other);
    virtual ~ShrubberyCreationForm();

    std::string const &getTarget() const;

    class FileOpenException : public std::exception
    {
        public:
            virtual const char *what() const throw();
    };
};

#endif
