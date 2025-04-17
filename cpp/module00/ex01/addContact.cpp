/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addContact.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:24:32 by smoore-a          #+#    #+#             */
/*   Updated: 2025/04/17 13:49:46 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

static int prompt(const std::string &request, std::string *arg)
{
	while (*arg == "")
	{
		std::cout << "Enter the " << request << " of the contact: ";
		getline(std::cin, *arg);
		if (std::cin.eof())
			return 1;
	}
	return 0;
}

static int getData(tContact *contact)
{
	std::string number;
	if (prompt("first name", &(contact->firstName)))
		return 1;
	if (prompt("last name", &(contact->lastName)))
		return 1;
	if (prompt("nickname", &(contact->nickname)))
		return 1;
	if (prompt("phone number", &(number)))
		return 1;
	if (prompt("darkest secret", &(contact->darkestSecret)))
		return 1;
	std::stringstream(number) >> contact->phoneNumber;
	return 0;
}

int PhoneBook::addContact(void)
{
	tContact contact;
	int index;

	if (getData(&contact))
		return 1;
	index = this->getLastIndex();
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
	return 0;
}
