/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 18:51:56 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/04/28 20:49:04 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <string>

class Contact
{
private:
    std::string firstName;
    std::string lastName;
    std::string nickname;
    std::string phoneNumber;
    std::string darkestSecret;

public:
    void setContact(std::string first, std::string last, std::string nick,
                    std::string phone, std::string secret);

    std::string getFirstName(void) const;
    std::string getLastName(void) const;
    std::string getNickname(void) const;
    std::string getPhoneNumber(void) const;
    std::string getDarkestSecret(void) const;
};

#endif
