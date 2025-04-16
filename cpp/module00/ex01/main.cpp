/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:35:06 by smoore-a          #+#    #+#             */
/*   Updated: 2025/04/16 14:02:03 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

static bool menu(const std::string &command, PhoneBook *phoneBook)
{
	if (command == "ADD")
		phoneBook->addContact();
	else if (command == "SEARCH" && phoneBook->getContact()[0].getInUse())
		phoneBook->searchContact();
	else if (command == "EXIT")
		return true;
	return false;
}

int main(void)
{
	std::string command;
	PhoneBook phoneBook;
	while (1)
	{
		std::cout << "Enter a command(ADD, SEARCH, EXIT): ";
		getline(std::cin, command);
		if (menu(command, &phoneBook))
			break;
	}
	return 0;
}
