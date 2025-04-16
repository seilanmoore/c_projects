/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:03:30 by smoore-a          #+#    #+#             */
/*   Updated: 2025/04/16 11:55:38 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include "Contact.hpp"
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdlib>

typedef struct sContact
{
	std::string darkestSecret;
	std::string firstName;
	std::string lastName;
	std::string nickname;
	unsigned int phoneNumber;
} tContact;

class PhoneBook
{
public:
	PhoneBook(void) : last_index_(0) {};
	~PhoneBook(void) {};

	void addContact(void);
	void display(void) const;
	const Contact *getContact(void);
	int getLastIndex(void) const;
	void searchContact(void) const;
	void setLastIndex(const int index);
	void showContact(const int index) const;

private:
	Contact contact_[8];
	int last_index_;
};

#endif
