/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 04:17:10 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/10/11 04:17:11 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "Intern.hpp"

static void processForm(Intern const &intern, Bureaucrat const &bureaucrat,
                        std::string const &formName, std::string const &target)
{
    AForm *form = intern.makeForm(formName, target);

    if (!form)
        return;
    std::cout << *form << std::endl;
    bureaucrat.signForm(*form);
    bureaucrat.executeForm(*form);
    delete form;
}

int main()
{
    try
    {
        Intern someRandomIntern;
        Bureaucrat president("President", 1);
        Bureaucrat clerk("Clerk", 140);

        std::cout << "\n--- Subject example ---" << std::endl;
        AForm *rrf = someRandomIntern.makeForm("robotomy request", "Bender");
        if (rrf)
        {
            president.signForm(*rrf);
            president.executeForm(*rrf);
            delete rrf;
        }

        std::cout << "\n--- All forms with a high-grade bureaucrat ---" << std::endl;
        processForm(someRandomIntern, president, "shrubbery creation", "garden");
        processForm(someRandomIntern, president, "robotomy request", "Marvin");
        processForm(someRandomIntern, president, "presidential pardon", "Arthur Dent");

        std::cout << "\n--- All forms with a low-grade bureaucrat ---" << std::endl;
        processForm(someRandomIntern, clerk, "shrubbery creation", "office");
        processForm(someRandomIntern, clerk, "robotomy request", "Marvin");
        processForm(someRandomIntern, clerk, "presidential pardon", "Arthur Dent");

        std::cout << "\n--- Unknown form name ---" << std::endl;
        processForm(someRandomIntern, president, "coffee request", "Boss");
    }
    catch (std::exception &e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
    return 0;
}
