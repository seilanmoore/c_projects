/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchContact.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:54:19 by smoore-a          #+#    #+#             */
/*   Updated: 2025/04/17 13:51:25 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

static std::string truncateToTen(const std::string &fullStr)
{
	if (fullStr.length() <= 10)
		return fullStr;
	else
		return fullStr.substr(0, 9) + '.';
}

static void displayAttribute(const std::string &attribute)
{
	std::cout << std::setw(10) << truncateToTen(attribute);
}

void PhoneBook::display(void) const
{
	int i;

	std::cout << std::right
			  << std::setw(10) << "index" << "|"
			  << std::setw(10) << "first name" << "|"
			  << std::setw(10) << "last name" << "|"
			  << std::setw(10) << "nickname" << std::endl;
	i = -1;
	while (++i < 8 && this->contact_[i].getInUse())
	{
		std::cout << std::right
				  << std::setw(10) << i + 1 << "|";
		displayAttribute(this->contact_[i].getFirstName());
		std::cout << "|";
		displayAttribute(this->contact_[i].getLastName());
		std::cout << "|";
		displayAttribute(this->contact_[i].getNickname());
		std::cout << std::endl;
	}
}

void PhoneBook::showContact(const int index) const
{
	std::cout << "First name: "
			  << this->contact_[index].getFirstName() << std::endl;
	std::cout << "Last name: "
			  << this->contact_[index].getLastName() << std::endl;
	std::cout << "Nickname: "
			  << this->contact_[index].getNickname() << std::endl;
	std::cout << "Phone number: "
			  << this->contact_[index].getPhoneNumber() << std::endl;
	std::cout << "Darkest secret: "
			  << this->contact_[index].getDarkestSecret() << std::endl;
}

int PhoneBook::searchContact(void) const
{
	int index;
	std::string number;

	this->display();
	index = 0;
	while (1)
	{
		std::cout << "Which contact do you want to display [1-8]: ";
		getline(std::cin, number);
		if (std::cin.eof())
			return 1;
		std::stringstream(number) >> index;
		if (index >= 1 && index <= 8)
		{
			index--;
			if (this->contact_[index].getInUse())
				this->showContact(index);
			else
				std::cout << "Contact does not exist" << std::endl;
			break;
		}
	}
	return 0;
}
