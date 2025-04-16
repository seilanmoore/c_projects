/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addContact.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:24:32 by smoore-a          #+#    #+#             */
/*   Updated: 2025/04/16 13:47:47 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

static void prompt(const std::string &request, std::string *arg)
{
	while (*arg == "")
	{
		std::cout << "Enter the " << request << " of the contact: ";
		getline(std::cin, *arg);
	}
}

static void getData(tContact *contact)
{
	std::string number;
	prompt("first name", &(contact->firstName));
	prompt("last name", &(contact->lastName));
	prompt("nickname", &(contact->nickname));
	prompt("phone number", &(number));
	prompt("darkest secret", &(contact->darkestSecret));
	std::stringstream(number) >> contact->phoneNumber;
}

void PhoneBook::addContact(void)
{
	tContact contact;
	int index = this->getLastIndex();
	getData(&contact);
	this->contact_[index].setDarkestSecret(contact.darkestSecret);
	this->contact_[index].setInUse(true);
	this->contact_[index].setFirstName(contact.firstName);
	this->contact_[index].setLastName(contact.lastName);
	this->contact_[index].setNickname(contact.nickname);
	this->contact_[index].setPhoneNumber(contact.phoneNumber);
	if (index == 7)
		this->setLastIndex(0);
	else
		this->setLastIndex(++index);
}
