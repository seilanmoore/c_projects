/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contactSetters.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 23:43:11 by smoore-a          #+#    #+#             */
/*   Updated: 2025/04/15 22:59:25 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

void Contact::setInUse(const bool inUse)
{
	this->in_use_ = inUse;
}

void Contact::setFirstName(const std::string &firstName)
{
	this->first_name_ = firstName;
}

void Contact::setLastName(const std::string &lastName)
{
	this->last_name_ = lastName;
}

void Contact::setNickname(const std::string &nickname)
{
	this->nickname_ = nickname;
}

void Contact::setDarkestSecret(const std::string &darkestSecret)
{
	this->darkest_secret_ = darkestSecret;
}

void Contact::setPhoneNumber(const unsigned int phoneNumber)
{
	this->phone_number_ = phoneNumber;
}
