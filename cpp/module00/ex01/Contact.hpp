/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:59:46 by smoore-a          #+#    #+#             */
/*   Updated: 2025/04/16 11:55:43 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_H
#define CONTACT_H

#include <iostream>

class Contact
{
public:
	Contact(void);
	~Contact(void) {};

	std::string getDarkestSecret(void) const;
	std::string getFirstName(void) const;
	bool getInUse(void) const;
	std::string getLastName(void) const;
	std::string getNickname(void) const;
	unsigned int getPhoneNumber(void) const;
	void setDarkestSecret(const std::string &darkestSecret);
	void setFirstName(const std::string &firstName);
	void setInUse(const bool inUse);
	void setLastName(const std::string &lastName);
	void setNickname(const std::string &nickname);
	void setPhoneNumber(const unsigned int phoneNumber);

private:
	std::string darkest_secret_;
	std::string first_name_;
	int index_;
	bool in_use_;
	std::string last_name_;
	std::string nickname_;
	unsigned int phone_number_;
};
#endif
