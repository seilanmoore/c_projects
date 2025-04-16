/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contactGetters.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 23:42:15 by smoore-a          #+#    #+#             */
/*   Updated: 2025/04/15 22:59:32 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

bool Contact::getInUse(void) const
{
	return this->in_use_;
}

std::string Contact::getFirstName(void) const
{
	return this->first_name_;
}

std::string Contact::getLastName(void) const
{
	return this->last_name_;
}

std::string Contact::getNickname(void) const
{
	return this->nickname_;
}

std::string Contact::getDarkestSecret(void) const
{
	return this->darkest_secret_;
}

unsigned int Contact::getPhoneNumber(void) const
{
	return this->phone_number_;
}
