/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 18:51:49 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/04/28 20:49:02 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

void Contact::setContact(std::string first, std::string last, std::string nick,
                         std::string phone, std::string secret)
{
    firstName = first;
    lastName = last;
    nickname = nick;
    phoneNumber = phone;
    darkestSecret = secret;
}

std::string Contact::getFirstName(void) const
{
    return firstName;
}

std::string Contact::getLastName(void) const
{
    return lastName;
}

std::string Contact::getNickname(void) const
{
    return nickname;
}

std::string Contact::getPhoneNumber(void) const
{
    return phoneNumber;
}

std::string Contact::getDarkestSecret(void) const
{
    return darkestSecret;
}
