/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 18:53:26 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/04/28 20:49:14 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include <iostream>
#include <iomanip>

PhoneBook::PhoneBook(void)
{
    index = 0;
    count = 0;
}

static std::string getInput(std::string prompt)
{
    std::string input;

    while (input.empty())
    {
        std::cout << prompt;
        std::getline(std::cin, input);

        if (input.empty())
            std::cout << "Field cannot be empty." << std::endl;
    }
    return input;
}

static std::string formatField(std::string str)
{
    if (str.length() > 10)
        return str.substr(0, 9) + ".";
    return str;
}

void PhoneBook::addContact(void)
{
    std::string first;
    std::string last;
    std::string nick;
    std::string phone;
    std::string secret;

    first = getInput("First Name: ");
    last = getInput("Last Name: ");
    nick = getInput("Nickname: ");
    phone = getInput("Phone Number: ");
    secret = getInput("Darkest Secret: ");

    contacts[index].setContact(first, last, nick, phone, secret);

    index = (index + 1) % 8;
    if (count < 8)
        count++;

    std::cout << "Contact saved." << std::endl;
}

void PhoneBook::searchContact(void) const
{
    std::string input;
    int id;

    if (count == 0)
    {
        std::cout << "PhoneBook is empty." << std::endl;
        return;
    }

    std::cout << "|"
              << std::setw(10) << "Index" << "|"
              << std::setw(10) << "First Name" << "|"
              << std::setw(10) << "Last Name" << "|"
              << std::setw(10) << "Nickname" << "|"
              << std::endl;

    for (int i = 0; i < count; i++)
    {
        std::cout << "|"
                  << std::setw(10) << i << "|"
                  << std::setw(10) << formatField(contacts[i].getFirstName()) << "|"
                  << std::setw(10) << formatField(contacts[i].getLastName()) << "|"
                  << std::setw(10) << formatField(contacts[i].getNickname()) << "|"
                  << std::endl;
    }

    std::cout << "Enter index: ";
    std::getline(std::cin, input);

    if (input.length() != 1 || input[0] < '0' || input[0] > '7')
    {
        std::cout << "Invalid index." << std::endl;
        return;
    }

    id = input[0] - '0';

    if (id >= count)
    {
        std::cout << "Invalid index." << std::endl;
        return;
    }

    std::cout << "First Name: " << contacts[id].getFirstName() << std::endl;
    std::cout << "Last Name: " << contacts[id].getLastName() << std::endl;
    std::cout << "Nickname: " << contacts[id].getNickname() << std::endl;
    std::cout << "Phone Number: " << contacts[id].getPhoneNumber() << std::endl;
    std::cout << "Darkest Secret: " << contacts[id].getDarkestSecret() << std::endl;
}
