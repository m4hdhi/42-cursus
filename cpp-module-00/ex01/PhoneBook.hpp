/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 18:53:33 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/04/28 20:49:16 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"

class PhoneBook
{
private:
    Contact contacts[8];
    int index;
    int count;

public:
    PhoneBook(void);
    void addContact(void);
    void searchContact(void) const;
};

#endif
