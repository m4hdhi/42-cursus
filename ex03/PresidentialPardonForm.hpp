/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 04:17:25 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/10/11 04:17:26 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRESIDENTIAL_PARDON_FORM_HPP
# define PRESIDENTIAL_PARDON_FORM_HPP

# include <string>
# include "AForm.hpp"

class PresidentialPardonForm : public AForm
{
private:
    std::string _target;

protected:
    void executeAction() const;

public:
    PresidentialPardonForm();
    PresidentialPardonForm(std::string const &target);
    PresidentialPardonForm(PresidentialPardonForm const &other);
    PresidentialPardonForm &operator=(PresidentialPardonForm const &other);
    virtual ~PresidentialPardonForm();

    std::string const &getTarget() const;
};

#endif
