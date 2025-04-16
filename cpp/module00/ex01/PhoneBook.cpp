/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:02:27 by smoore-a          #+#    #+#             */
/*   Updated: 2025/04/16 11:44:42 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

void PhoneBook::setLastIndex(const int index)
{
	this->last_index_ = index;
}

int PhoneBook::getLastIndex(void) const
{
	return this->last_index_;
}

const Contact *PhoneBook::getContact(void)
{
	return this->contact_;
}
